#ifndef SUCCOTASH_VIEW_HPP
#define SUCCOTASH_VIEW_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <functional>

namespace succotash {
class Layout;

class View : public sf::RectangleShape {
  View *parent_;
  std::vector<View *> sons_;
  Layout *layout_;

  std::function<bool(View *)> click_listener_;

public:
  int id_;

  View();

  void SetLayout(Layout *layout);
  Layout * GetLayout() const;

  virtual void AddSon(View *view);
  virtual void InsertBefore(View *to_insert, View *before_what);
  virtual bool RemoveSon(View *view);

  bool HandleClick(const sf::Vector2i& pos) const;

  void SetClickListener(std::function<bool(View *)>);
  std::function<bool(View *)> GetClickListener() const;

  void Draw() const;
  virtual void DrawSelf() const;
};
}


#endif // SUCCOTASH_VIEW_HPP
