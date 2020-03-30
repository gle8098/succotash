#include "view.hpp"


namespace succotash {


View::View()
    : shape_(),
      layout_(nullptr),
      parent_(nullptr),


}

void View::AddSon(View* view) const {
  sons_.push_back(view);
  view.parent_ = view;
  layout_.Place(sons_);
}

Result<View*> View::HandleClick(const sf::Vector2i &pos) const {
  if (!shape_->getGlobalBounds().contains(pos)) {
    // TODO: this if converts pos.{x,y} to float
    return Result(false);
  }
  Result<View*> son_func(false);
  for (View* son : sons_) {
    son_func = son->HandleClick(pos);
    if (son_func != ) {
      return son_func;
    }
  }
  return InvokeHandler();
}

Result<View*> View::InvokeHandler() {
  return Result(false);
}

void View::DrawSelf() const {}

} // succotash

