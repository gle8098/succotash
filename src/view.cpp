#include "view.hpp"

#include <algorithm>
#include <utility>

#include "layout.hpp"
#include "utilities/Convertible.hpp"

namespace succotash {

View::View()
    : shape_(),
      layout_(nullptr),
      parent_(nullptr),
      id_(0) {
}

//------------------------------------------------------------------------------
// Public static.
//------------------------------------------------------------------------------

View* View::Construct(const utilities::StringHashTable<utilities::Convertible>& params, View* view) {
  if (view == nullptr) {
    view = new View();
  }
  if (params.find("id") != params.end()) {
    view->SetId(params.at("id").ToInt());
  }
  return view;
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
  InvokeLayout();
}

void View::InsertSonBefore(std::vector<View*>::const_iterator position,
                           View* view) {
  sons_.insert(position, view);
  view->parent_ = view;
  InvokeLayout();
}

bool View::RemoveSon(View* view) {
  auto it = std::find(sons_.begin(), sons_.end(), view);
  if (it != sons_.end()) {
    sons_.erase(it);
    view->parent_ = nullptr;
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
  for (View* son : sons_) {
    son->MoveBy(offset);
  }
  shape_.setPosition(new_pos);
}

void View::MoveBy(const sf::Vector2f& offset) {
  for (View* son : sons_) {
    son->MoveBy(offset);
  }
  shape_.move(offset);
}

void View::Resize(const sf::Vector2f& new_size) {
  shape_.setSize(new_size);
}

//------------------------------------------------------------------------------
// Set & Get.
//------------------------------------------------------------------------------

int View::GetId() const { return id_; }
void View::SetId(int id) { id_ = id; }

void View::SetLayout(Layout* layout) {
  layout_ = layout;
  InvokeLayout();
}

const Layout*             View::GetLayout() const { return layout_; }
View*                     View::GetParent() const { return parent_; }
const std::vector<View*>& View::GetSons()   const { return sons_;   }
sf::RectangleShape        View::GetShape()  const { return shape_;  }

//------------------------------------------------------------------------------
// Protected.
//------------------------------------------------------------------------------

void View::InvokeLayout() const {
  if (layout_) {
    // 'This' is a parent of its sons, so Place arg is correct.
    layout_->Place(this);
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

} // succotash

