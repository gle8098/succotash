#include "view.hpp"
#include <algorithm>


namespace succotash {


View::View()
    : shape_(),
      layout_(nullptr),
      parent_(nullptr),
      id_(0) {


}

int View::GetId() const { return id_; }
void View::SetId(int id) { id_ = id; }

void View::SetLayout(Layout* layout) {
  layout_ = layout;
  InvokeLayout();
}

const Layout* View::GetLayout() const { return layout_; }

View* View::GetParent() const { return parent_; }

const std::vector<View*>& View::GetSons() const { return sons_; }

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

bool View::IsPointWithinBounds(const sf::Vector2i &point) const {
  return shape_.getGlobalBounds().contains(point.x, point.y);
}

bool View::OnClickEvent(View* clicked_view) const { return false; }

void View::Draw(sf::RenderWindow &window) const {
  for (View* son : sons_) {
    son->Draw(window);
  }
  DrawSelf(window);
}

void View::InvokeLayout() const {
  if (layout_) {
    // This is a parent of its sons, so Place arg is correct.
    layout_->Place(this);
  }
}

void View::DrawSelf(sf::RenderWindow& window) const { /* empty* / }

} // succotash

