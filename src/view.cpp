#include "view.hpp"

#include <algorithm>
#include <utility>

#include "layout.hpp"


namespace succotash {

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

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

void View::Draw(sf::RenderWindow& display) const {
  for (auto son : sons_) {
    son->Draw(display);
  }
  DrawSelf(display);
}

void View::AddSon(ViewPtr view) {
  sons_.push_back(view);
  view->parent_ = view;
  UpdateLayoutParams(view);
  InvokeLayout();
}

void View::InsertSonBefore(std::vector<ViewPtr>::const_iterator position,
                           ViewPtr view) {
  sons_.insert(position, view);
  view->parent_ = view;
  UpdateLayoutParams(view);
  InvokeLayout();
}

bool View::RemoveSon(ViewPtr view) {
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

ViewPtr View::HandleClick(const sf::Vector2i& click_pos) {
  ViewPtr clicked_view = nullptr;

  for (auto son : sons_) {
    if (son->IsPointWithinBounds(click_pos)) {
      clicked_view = son->HandleClick(click_pos);
      break;
    }
  }

  OnClickEvent(clicked_view);

  if (clicked_view == nullptr) {  // Current view is the deepest one.
    return shared_from_this();
  }
  return clicked_view;
}

void View::OnClickEvent(ViewPtr clicked_view) { /* Virtual */ }

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

int                         View::GetId()     const { return id_;     }
const LayoutPtr             View::GetLayout() const { return layout_; }
ViewPtr                     View::GetParent() const { return parent_; }
const std::vector<ViewPtr>& View::GetSons()   const { return sons_;   }
sf::RectangleShape          View::GetShape()  const { return shape_;  }

//------------------------------------------------------------------------------
// Protected.
//------------------------------------------------------------------------------

void View::InvokeLayout() const {
  if (layout_) {
    layout_->Place(sons_, shape_);
  }
  for (ViewPtr son : sons_) {
    son->InvokeLayout();
  }
}

void View::DrawSelf(sf::RenderWindow& display) const { /* Virtual */ }

void View::SetDispositionParams(LayoutParamsPtr disposition_params) {
  disposition_params_ = disposition_params;
}

const LayoutParamsPtr View::GetDispositionParams() const {
  return disposition_params_;
}

ViewPtr View::FindViewById(int id) {
  if (id_ == id) {
    return shared_from_this();
  }
  for (auto son : sons_) {
    ViewPtr needle = son->FindViewById(id);
    if (needle != nullptr) {
      return needle;
    }
  }
  return nullptr;
}

void View::UpdateLayoutParams(ViewPtr son) const {
  if (layout_ == nullptr) {
    return;
  }
  if (!layout_->AreParametersOfMyClass(son->GetDispositionParams())) {
    son->SetDispositionParams(layout_->CreateDefaultParams());
  }
}

} // succotash

