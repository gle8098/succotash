#ifndef SUCCOTASH_VIEW_HPP
#define SUCCOTASH_VIEW_HPP
#include <SFML/Graphics.hpp>
#include <vector>

#include "utilities/StringHashTable.hpp"
#include "utilities/ptr.hpp"
// TODO: remove above StringHashTable include when will be possible

namespace succotash {

// Dependencies
namespace utilities {
  class Convertible;
}

class Layout;
using LayoutPtr = std::shared_ptr<Layout>;

class LayoutParams;
using LayoutParamsPtr = std::shared_ptr<LayoutParams>;


class View {
protected:
  using Params = utilities::StringHashTable<utilities::Convertible>;

public:
  View();
  View(const Params& params);
  virtual ~View();

  void Draw(sf::RenderWindow& display) const;

  /// Resize sons_ array to count sons.
  void ReserveSons(size_t count);
  virtual void AddSon(View* view);
  virtual void InsertSonBefore(std::vector<View*>::const_iterator position,
                               View* view);
  virtual bool  RemoveSon(View* view);
  virtual View* GetSon(size_t index) const;
  /// Replace son by index.
  virtual void  SetSon(size_t index, View* new_son);

  bool    IsPointWithinBounds(const sf::Vector2i& point) const;
  View* HandleClick(const sf::Vector2i& click_pos);

  virtual void OnClickEvent(View* clicked_view);

  virtual void MoveTo(const sf::Vector2f& new_pos);
  virtual void MoveBy(const sf::Vector2f& offset);
  virtual void Resize(const sf::Vector2f& new_size);

  void SetId(int id);
  void SetLayout(LayoutPtr layout);
  void SetDispositionParams(LayoutParamsPtr disposition_params);

  int                       GetId()     const;
  const LayoutPtr           GetLayout() const;
  View*                     GetParent() const;
  const std::vector<View*>& GetSons()   const;
  sf::RectangleShape        GetShape()  const;
  const LayoutParamsPtr     GetDispositionParams() const;

  View* FindViewById(int id);

protected:
  void UpdateLayoutParams(View* son) const;
  void InvokeLayout() const;

  virtual void DrawSelf(sf::RenderWindow& display) const;

private:
  void Init();
  void UpdateSon(View* son);

// === Data ===

protected:
  sf::RectangleShape shape_;
  LayoutPtr layout_;

private:
  std::vector<View*> sons_;
  View* parent_;
  int id_;
  LayoutParamsPtr disposition_params_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
