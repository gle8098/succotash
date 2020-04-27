#ifndef SUCCOTASH_VIEW_HPP
#define SUCCOTASH_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <StringHashTable.hpp>


namespace succotash {

class Layout;

class View {
public:
  View();
  ~View() = default;

  void Draw(sf::RenderWindow& display) const;

  void AddSon(View* view);
  void InsertSonBefore(std::vector<View*>::const_iterator position, View* view);
  bool RemoveSon(View* view);

  bool IsPointWithinBounds(const sf::Vector2i& point) const;
  View* HandleClick(const sf::Vector2i& click_pos);
  virtual void OnClickEvent(View* clicked_view);

  virtual void MoveTo(const sf::Vector2f& new_pos);
  virtual void MoveBy(const sf::Vector2f& offset);
  virtual void Resize(const sf::Vector2f& new_size);

  void SetId(int id); // Should not have external access (move to private). WRONG!!!!!!! MUST BE PUBLIC
  void SetLayout(Layout* layout);

  void SetParentLayoutParams(StringHashTable<std::string> parent_layout_params);

  int                       GetId()     const;
  const Layout*             GetLayout() const;
  View*                     GetParent() const;
  const std::vector<View*>& GetSons()   const;
  sf::RectangleShape        GetShape()  const;
  const StringHashTable<std::string>& GetParentLayoutParams() const;

  View* FindViewById(int id);

protected:
  void InvokeLayout() const;

  virtual void DrawSelf(sf::RenderWindow& display) const;

// === Data ===

protected:
  sf::RectangleShape shape_;
  Layout* layout_;

private:
  View* parent_;
  std::vector<View*> sons_;
  int id_;
  StringHashTable<std::string> parent_layout_params_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
