#include "view.hpp"

#include <algorithm>
#include <utility>

#include "layout.hpp"
#include "default_layout.hpp"
#include "utilities/assert.hpp"

namespace succotash {

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

View::View() {
  Init();
}

View::View(const Params& params) {
  Init();

  Params::const_iterator it;
  if ((it = params.find("id")) != params.end()) {
    SetId(it->second.ToInt());
  }

  sf::Vector2f critical_size(0, 0);
  if ((it = params.find("criticalWidth")) != params.end()) {
    critical_size.x = it->second.ToFloat();
  }
  if ((it = params.find("criticalHeight")) != params.end()) {
    critical_size.y = it->second.ToFloat();
  }
  SetCriticalSize(critical_size);
}

void View::Init() {
  rect_ = sf::FloatRect(0, 0, 0, 0);
  layout_ = CreatePtr<DefaultLayout>();
  parent_ = nullptr;
  id_ = 0;
  disposition_params_ = nullptr;
  critical_size_ = {0, 0};
}

View::~View() {
  for (auto son: sons_) {
    delete son;
  }
}

//------------------------------------------------------------------------------
// Public.
//------------------------------------------------------------------------------

bool View::IsPointWithinBounds(const sf::Vector2i& point) const {
  return rect_.contains(point.x, point.y);
}

void View::Draw(sf::RenderWindow& display) const {
  DrawSelf(display);
  for (auto son : sons_) {
    son->Draw(display);
  }
}

// Sons.

void View::AddSon(View* view) {
  InsertSonBefore(sons_.end(), view);
}

void View::InsertSonBefore(std::vector<View*>::const_iterator position,
                           View* view) {
  sons_.insert(position, view);
  UpdateSon(view);
  UpdateCriticalSize(view->GetCriticalSize());
}

bool View::RemoveSon(View* view) {
  auto it = std::find(sons_.begin(), sons_.end(), view);
  if (it != sons_.end()) {
    delete *it;
    sons_.erase(it);
    InvokeLayout();
    return true;
  }
  return false;
}

View* View::GetSon(size_t index) const {
  ASSERT(index < sons_.size());

  return sons_[index];
}

void View::SetSon(size_t index, View* new_son) {
  if (sons_[index] == new_son) {
    return;
  }

  ASSERT(index < sons_.size());
  //delete sons_[index];        This line breaks program.

  sons_[index] = new_son;
  UpdateSon(new_son);
}

View* View::HandleClick(const sf::Vector2i& click_pos) {
  View* clicked_view = nullptr;

  for (auto son : sons_) {
    if (son->IsPointWithinBounds(click_pos)) {
      clicked_view = son->HandleClick(click_pos);
      break;
    }
  }

  OnClickEvent(clicked_view);

  if (clicked_view == nullptr) {  // Current view is the deepest one.
    return this;
  }
  return clicked_view;
}

void View::OnClickEvent(View* clicked_view) { /* Virtual */ }

void View::MoveTo(const sf::Vector2f& new_pos) {
  MoveBy(sf::Vector2f(new_pos.x - rect_.left, new_pos.y - rect_.top));
}

void View::MoveBy(const sf::Vector2f& offset) {
  if (offset.x == offset.x) { // Nan check.
    rect_.left += offset.x;
  }
  if (offset.y == offset.y) {
    rect_.top += offset.y;
  }
  for (auto son : sons_) {  // We might use InvokeLayout, but it's faster.
    son->MoveBy(offset);
  }
}

void View::Resize(const sf::Vector2f& new_size) {
  if (new_size.x == new_size.x) {
    rect_.width  = new_size.x;
  }
  if (new_size.y == new_size.y) {
    rect_.height = new_size.y;
  }
  InvokeLayout(); // Layout will align sons.
}

//------------------------------------------------------------------------------
// Set & Get.
//------------------------------------------------------------------------------

void View::SetId(int id) {
  id_ = id;
}

void View::SetLayout(LayoutPtr layout) {
  layout_ = layout;
  for (auto son : sons_) {
    UpdateLayoutParams(son);
  }
  InvokeLayout();
}

int                       View::GetId()     const { return id_;     }
const LayoutPtr           View::GetLayout() const { return layout_; }
View*                     View::GetParent() const { return parent_; }
const std::vector<View*>& View::GetSons()   const { return sons_;   }
sf::FloatRect             View::GetRect()   const { return rect_;   }

//------------------------------------------------------------------------------
// Protected.
//------------------------------------------------------------------------------

void View::InvokeLayout() const {
  if (layout_) {
    layout_->Place(sons_, GetRect());
  }
  for (auto son : sons_) {
    if (son != nullptr) {
      son->InvokeLayout();
    }
  }
}

void View::DrawSelf(sf::RenderWindow& display) const {
  /* View is not drawable. */
}

void View::SetDispositionParams(LayoutParamsPtr disposition_params) {
  disposition_params_ = disposition_params;
}

void View::SetCriticalSize(const sf::Vector2f& critical_size) {
  critical_size_ = critical_size;
  if (GetParent() != nullptr) {
    GetParent()->UpdateCriticalSize(critical_size_);
  }
}

void View::UpdateCriticalSize(const sf::Vector2f& critical_size) {
  bool size_updated = false;

  if (critical_size_.x < critical_size.x) {
    critical_size_.x = critical_size.x;
    size_updated = true;
  }
  if (critical_size_.y < critical_size.y) {
    critical_size_.y = critical_size.y;
    size_updated = true;
  }

  if (size_updated && GetParent() != nullptr) {
    GetParent()->UpdateCriticalSize(critical_size_);
  }
}

void View::DeleteCriticalSize(const sf::Vector2f& critical_size) {
  bool size_updated = false;

  if (critical_size_.x == critical_size.x) {  // Potential "bottle neck" son.
    critical_size_.x = 0;
    for (auto son : sons_) {
      auto son_critical_size = son->GetCriticalSize();
      // Search for smallest x size of sons.
      if (critical_size_.x < son_critical_size.x || critical_size_.x == 0) {
        critical_size_.x = son_critical_size.x;
      }
    }
    ASSERT(critical_size_.x <= critical_size.x);
    if (critical_size_.x != critical_size.x) {
      size_updated = true;
    }
  }
  if (critical_size_.y < critical_size.y) {
    critical_size_.y = 0;
    for (auto son : sons_) {
      auto son_critical_size = son->GetCriticalSize();

      if (critical_size_.y < son_critical_size.y || critical_size_.y == 0) {
        critical_size_.y = son_critical_size.y;
      }
    }
    ASSERT(critical_size_.y <= critical_size.y);
    if (critical_size_.y != critical_size.y) {
      size_updated = true;
    }
  }

  if (size_updated && GetParent() != nullptr) {
    GetParent()->DeleteCriticalSize(critical_size);
  }
}

const LayoutParamsPtr View::GetDispositionParams() const {
  return disposition_params_;
}

sf::Vector2f View::GetCriticalSize() const {
  return critical_size_;
}

View* View::FindViewById(int id) {
  if (id_ == id) {
    return this;
  }
  for (auto son : sons_) {
    View* needle = son->FindViewById(id);
    if (needle != nullptr) {
      return needle;
    }
  }
  return nullptr;
}

void View::UpdateLayoutParams(View* son) const {
  if (layout_ == nullptr || son == nullptr) {
    return;
  }
  if (!layout_->AreParametersOfMyClass(son->GetDispositionParams())) {
    son->SetDispositionParams(layout_->CreateDefaultParams());
  }
}

void View::UpdateSon(View* son) {
  if (son != nullptr) {
    son->parent_ = this;
    UpdateLayoutParams(son);
    InvokeLayout();
  }
}

} // succotash

