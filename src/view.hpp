#ifndef SUCCOTASH_VIEW_HPP
#define SUCCOTASH_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>


namespace succotash {

class Layout;


class View {
public:
  View();
  ~View() = default;

  bool IsPointWithinBounds(const sf::Vector2i& point) const;
  void Draw(sf::RenderWindow& window) const;

  void AddSon(View* view);
  void InsertSonBefore(std::vector<View*>::const_iterator position, View* view);
  bool RemoveSon(View* view);

  virtual bool OnClickEvent(View* clicked_view) const;

  virtual void MoveTo(const sf::Vector2f& new_pos);
  virtual void Resize(const sf::Vector2f& new_size);

  void SetId(int id); // Should not have external access (move to private).
  void SetLayout(Layout* layout);

  int                       GetId() const;
  const Layout*             GetLayout() const;
  View*                     GetParent() const;
  const std::vector<View*>& GetSons() const;
  sf::RectangleShape        GetShape() const;

protected:
  void InvokeLayout() const;

  virtual void DrawSelf(sf::RenderWindow& window) const;

// Fields.
protected:
  sf::RectangleShape shape_;
  Layout* layout_;

private:
  View* parent_;
  std::vector<View*> sons_;

  int id_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
