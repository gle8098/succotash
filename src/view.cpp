#include "view.hpp"

#include <algorithm>
#include <utility>

#include "layout.hpp"

namespace succotash {

View::View()
    : shape_(),
      layout_(nullptr),
      parent_(nullptr),
      id_(0) {
}

View::View(const Params& params) {
  if (params.find("id") != params.end()) {
    SetId(params.at("id").ToInt());
  }
}

//------------------------------------------------------------------------------
// Public.
//------------------------------------------------------------------------------

bool View::IsPointWithinBounds(const sf::Vector2i& point) const {
  return shape_.getGlobalBounds().contains(point.x, point.y);
}

void View::Draw(sf::RenderWindow &display) const {
  for (View* son : sons_) {
    son->Draw(display);
  }
  DrawSelf(display);
}

void View::AddSon(View* view) {
  sons_.push_back(view);
  view->parent_ = view;
  UpdateLayoutParams(view);
  InvokeLayout();
}

void View::InsertSonBefore(std::vector<View*>::const_iterator position,
                           View* view) {
  sons_.insert(position, view);
  view->parent_ = view;
  UpdateLayoutParams(view);
  InvokeLayout();
}

bool View::RemoveSon(View* view) {
  auto it = std::find(sons_.begin(), sons_.end(), view);
  if (it != sons_.end()) {
    sons_.erase(it);
    view->parent_ = nullptr;
    UpdateLayoutParams(view);
    InvokeLayout();
    return true;
  }
  return false;
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
  for (View* son : sons_) {
    son->MoveBy(offset);
  }
}

void View::MoveBy(const sf::Vector2f& offset) {
  shape_.move(offset);
  for (View* son : sons_) {
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

void View::SetLayout(Layout* layout) {
  layout_ = layout;
  for (auto& son : sons_) {
    UpdateLayoutParams(son);
  }
  InvokeLayout();
}

int                       View::GetId()     const { return id_;     }
const Layout*             View::GetLayout() const { return layout_; }
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
  for (View* son : sons_) {
    son->InvokeLayout();
  }
}

void View::DrawSelf(sf::RenderWindow& display) const { /* Virtual */ }


void View::SetDispositionParams(LayoutParams* disposition_params) {
  disposition_params_ = std::move(disposition_params);
}
const LayoutParams* View::GetDispositionParams() const {
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
  if (layout_ == nullptr) {
    return;
  }
  if (!layout_->AreParametersOfMyClass(son->GetDispositionParams())) {
    // TODO: memory leak
    son->SetDispositionParams(layout_->CreateDefaultParams());
  }
}

} // succotash

