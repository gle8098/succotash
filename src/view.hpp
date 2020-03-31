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

  void SetId(int id);
  int GetId() const;

  void SetLayout(Layout* layout);
  const Layout* GetLayout() const;

  View* GetParent() const;
  const std::vector<View*>& GetSons() const;

  virtual void AddSon(View* view);
  virtual void InsertSonBefore(std::vector<View*>::const_iterator position,
                               View* view);
  virtual bool RemoveSon(View* view);

  sf::RectangleShape& GetViewShape();
  const sf::RectangleShape& GetViewShape() const;
  bool IsPointWithinBounds(const sf::Vector2i& point) const;

  void Draw(sf::RenderWindow& window) const;

  virtual bool OnClickEvent(View* clicked_view) const;

protected:
  void InvokeLayout() const;

  virtual void DrawSelf(sf::RenderWindow& window) const;

  sf::RectangleShape shape_;

private:
  Layout* layout_;

  View* parent_;
  std::vector<View*> sons_;

  int id_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
