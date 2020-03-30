#ifndef SUCCOTASH_VIEW_HPP
#define SUCCOTASH_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>


namespace succotash {

class Layout;


class View {
public:
  View();

  void SetLayout(Layout* layout);
  Layout* GetLayout() const;

  virtual void AddSon(View* view);
  virtual void InsertBefore(View* to_insert, View* before_what);
  virtual bool RemoveSon(View* view);

  Result<View*> HandleClick(const sf::Vector2i& pos) const;

  void Draw(sf::RenderWindow& window) const;

protected:
  virtual void DrawSelf(sf::RenderWindow& window) const;
  virtual Result<View*> InvokeHandler();

private:


private:
  sf::RectangleShape shape_;
  Layout* layout_;

  View* parent_;
  std::vector<View*> sons_;

  int id_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
