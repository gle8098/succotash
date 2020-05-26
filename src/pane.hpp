#ifndef PANE_HPP
#define PANE_HPP

#include "view.hpp"
#include "button.hpp"


namespace succotash {


class Tab : public Button {
public:
  Tab();
  Tab(const sf::String& string);
  Tab(const Params& params);
  ~Tab();

  void AddSon(View* view) override;

  View* GetContent() const { return content_; }
  void Activate()   { is_active_ = true; }
  void Deactivate() { is_active_ = false; }

  sf::String texture_;

private:
  void Init();

private:
  View* content_;
  bool is_active_;
};


class Pane : public Sprite {
public:
  Pane();
  Pane(const Params& params);
  ~Pane();

  void AddTab(Tab* tab);
  void SwitchTab(Tab* tab);
  Tab* GetActiveTab() const;

  /// Default head weight is 0.3 while content's weight is ummutable 1.
  void SetHeadWeight(float weight);

private:
  void Init();
  void OnClickEvent(View* clicked_view) override;

  void AddSon(View* view) override; // Private! Use AddTab instead.
  // TODO: override InsertBefore and RemoveSon

private:
  size_t head_id_;
  size_t content_id_;
  Tab* active_tab_;
};

} // succotash

#endif // PANE_HPP

