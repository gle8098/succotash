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

  if (params.find("id") != params.end()) {
    SetId(params.at("id").ToInt());
  }
}

View::~View() {
  for (auto son: sons_) {
    delete son;
  }
}

void View::Init() {
  layout_ = CreatePtr<DefaultLayout>();
  parent_ = nullptr;
  id_ = 0;
  disposition_params_ = nullptr;
}

//------------------------------------------------------------------------------
// Public.
//------------------------------------------------------------------------------

bool View::IsPointWithinBounds(const sf::Vector2i& point) const {
  return shape_.getGlobalBounds().contains(point.x, point.y);
}

void View::Draw(sf::RenderWindow& display) const {
  for (auto son : sons_) {
    son->Draw(display);
  }
  DrawSelf(display);
}

// Sons.

void View::ReserveSons(size_t count) {
  ASSERT_WARN(sons_.size() <= count);
  sons_.resize(count, nullptr);
}

void View::AddSon(View* view) {
  sons_.push_back(view);
  UpdateSon(view);
}

void View::InsertSonBefore(std::vector<View*>::const_iterator position,
                           View* view) {
  sons_.insert(position, view);
  UpdateSon(view);
}

bool View::RemoveSon(View* view) {
  auto it = std::find(sons_.begin(), sons_.end(), view);
  if (it != sons_.end()) {
    delete *it;
    sons_.erase(it);
    // old
    //view->parent_ = nullptr;
    //UpdateLayoutParams(view);
    InvokeLayout();
    return true;
  }
  return false;
}

View* View::GetSon(size_t index) const {
  ASSERT_WARN(index < sons_.size());

  return sons_[index];
}

void View::SetSon(size_t index, View* new_son) {
  ASSERT_WARN(index < sons_.size());

  delete sons_[index];

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
  auto offset = shape_.getPosition() - new_pos;

  shape_.setPosition(new_pos);
  for (auto son : sons_) {
    son->MoveBy(offset);
  }
}

void View::MoveBy(const sf::Vector2f& offset) {
  shape_.move(offset);
  for (auto son : sons_) {
    son->MoveBy(offset);
  }
}

void View::Resize(const sf::Vector2f& new_size) {
  // Should it recursively Resize sons in case layout_ == nullptr?
  shape_.setSize(new_size);
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
sf::RectangleShape        View::GetShape()  const { return shape_;  }

//------------------------------------------------------------------------------
// Protected.
//------------------------------------------------------------------------------

void View::InvokeLayout() const {
  if (layout_) {
    layout_->Place(sons_, shape_);
  }
  for (auto son : sons_) {
    if (son != nullptr) {
      son->InvokeLayout();
    }
  }
}

void View::DrawSelf(sf::RenderWindow& display) const { /* Virtual */ }

void View::SetDispositionParams(LayoutParamsPtr disposition_params) {
  disposition_params_ = disposition_params;
}

const LayoutParamsPtr View::GetDispositionParams() const {
  return disposition_params_;
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

