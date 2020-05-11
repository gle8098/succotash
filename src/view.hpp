#ifndef SUCCOTASH_VIEW_HPP
#define SUCCOTASH_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "utilities/StringHashTable.hpp"
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

class View;
using ViewPtr = std::shared_ptr<View>;


class View : public std::enable_shared_from_this<View> {
protected:
  using Params = utilities::StringHashTable<utilities::Convertible>;

public:
  View();
  View(const Params& params);
  virtual ~View() = default;

  void Draw(sf::RenderWindow& display) const;

  void AddSon(ViewPtr view);
  void InsertSonBefore(std::vector<ViewPtr>::const_iterator position,
                       ViewPtr view);
  bool RemoveSon(ViewPtr view);

  bool IsPointWithinBounds(const sf::Vector2i& point) const;
  ViewPtr HandleClick(const sf::Vector2i& click_pos);

  virtual void OnClickEvent(ViewPtr clicked_view);

  virtual void MoveTo(const sf::Vector2f& new_pos);
  virtual void MoveBy(const sf::Vector2f& offset);
  virtual void Resize(const sf::Vector2f& new_size);

  void SetId(int id);
  void SetLayout(LayoutPtr layout);

  void SetDispositionParams(LayoutParamsPtr disposition_params);

  int                         GetId()     const;
  const LayoutPtr             GetLayout() const;
  ViewPtr                     GetParent() const;
  const std::vector<ViewPtr>& GetSons()   const;
  sf::RectangleShape          GetShape()  const;
  const LayoutParamsPtr       GetDispositionParams() const;

  ViewPtr FindViewById(int id);

protected:
  void UpdateLayoutParams(ViewPtr son) const;
  void InvokeLayout() const;

  virtual void DrawSelf(sf::RenderWindow& display) const;

  template <typename Derived>
  std::shared_ptr<Derived> shared_from_base() {
    return std::static_pointer_cast<Derived>(shared_from_this());
  }

// === Data ===

protected:
  sf::RectangleShape shape_;
  LayoutPtr layout_;

private:
  ViewPtr parent_;
  std::vector<ViewPtr> sons_;
  int id_;
  LayoutParamsPtr disposition_params_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
