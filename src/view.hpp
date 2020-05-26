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

  virtual void AddSon(View* view);
  virtual void InsertSonBefore(std::vector<View*>::const_iterator position,
                               View* view);
  virtual bool  RemoveSon(View* view);
  virtual View* GetSon(size_t index) const;
  /// Replace son by index.
  virtual void  SetSon(size_t index, View* new_son);

  bool  IsPointWithinBounds(const sf::Vector2i& point) const;
  View* HandleClick(const sf::Vector2i& click_pos);

  virtual void OnClickEvent(View* clicked_view);

  virtual void MoveTo(const sf::Vector2f& new_pos);
  virtual void MoveBy(const sf::Vector2f& offset);
  virtual void Resize(const sf::Vector2f& new_size);

  void SetId(int id);
  void SetLayout(LayoutPtr layout);
  void SetDispositionParams(LayoutParamsPtr disposition_params);
  void SetFixedSize(const sf::Vector2f& fixed_size);

  void UpdateFixedSize(const sf::Vector2f& fixed_size);
  void DeleteFixedSize(const sf::Vector2f& fixed_size);

  int                       GetId()                const;
  const LayoutPtr           GetLayout()            const;
  View*                     GetParent()            const;
  const std::vector<View*>& GetSons()              const;
  sf::FloatRect             GetRect()              const;
  const LayoutParamsPtr     GetDispositionParams() const;
  /// GetFixedSize() == {0, 0} <==> size not fixed.
  sf::Vector2f              GetFixedSize()         const;

  View* FindViewById(int id);

protected:
  void UpdateLayoutParams(View* son) const;
  void InvokeLayout() const;

  virtual void DrawSelf(sf::RenderWindow& display) const;

private:
  // Used to solve a problem of base initializer and a delegation ctors.
  void Init();
  void UpdateSon(View* son);

// === Data ===

protected:
  LayoutPtr layout_;

private:
  sf::FloatRect rect_;
  std::vector<View*> sons_;
  View* parent_;
  int id_;
  LayoutParamsPtr disposition_params_;
  sf::Vector2f fixed_size_;
};

} // succotash


#endif // SUCCOTASH_VIEW_HPP
