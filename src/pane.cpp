#include "pane.hpp"
#include "linear_layout.hpp"
#include "utilities/assert.hpp"


namespace succotash {

//==============================================================================
// Tab.
//==============================================================================

Tab::Tab() {
  Init();
}

Tab::~Tab() {
  delete content_;
}

Tab::Tab(const sf::String& string)
    : Button(string) {
  Init();
}

Tab::Tab(const Params& params)
    : Button(params) {
  content_ = new View(params);
  is_active_ = false;
}

void Tab::Init() {
  content_ = new View;
  is_active_ = false;
}

void Tab::AddSon(View* view) {
  if (GetLayout() != nullptr) { // Check to be succeeded only once.
    // Exchange layouts.
    // We cannot do this in ctors, for by that moment layout isn't set yet.
    content_->SetLayout(GetLayout());
    content_->SetDispositionParams(GetDispositionParams());
    SetLayout(nullptr);
    SetDispositionParams(nullptr);
  }

  content_->AddSon(view);
}

//==============================================================================
// Pane.
//==============================================================================

//------------------------------------------------------------------------------
// Ctors.
//------------------------------------------------------------------------------

Pane::Pane() {
  Init();
}

Pane::Pane(const Params& params)
    : View(params) {

  Init();
}

void Pane::Init() {
  head_id_ = 0;
  content_id_ = 1;
  active_tab_ = nullptr;

  auto head = new View;
  auto content = new View;

  // Head
  auto head_params = CreatePtr<LinearLayoutParams>();

  head_params->weight = 3;
  head->SetDispositionParams(head_params);
  head->SetLayout(CreatePtr<LinearLayout>(LinearLayout::Type::Horizontal));

  // Content
  auto content_params = CreatePtr<LinearLayoutParams>();
  content_params->weight = 7;
  content->SetDispositionParams(content_params);
  content->AddSon(new View);

  //content_.SetLayout(CreatePtr LinearLayout(LinearLayout::Type::Vertical));

  // Pane
  SetLayout(CreatePtr<LinearLayout>(LinearLayout::Type::Vertical));

  View::AddSon(head);
  View::AddSon(content);
}

//------------------------------------------------------------------------------
// Methods.
//------------------------------------------------------------------------------

void Pane::AddTab(Tab* tab) {
  GetSon(head_id_)->AddSon(tab);
}

void Pane::SwitchTab(Tab* tab) {
  if (active_tab_ == tab) {
    return;
  }

  if (active_tab_) {
    active_tab_->Deactivate();
  }
  active_tab_ = tab;
  active_tab_->Activate();
  GetSon(content_id_)->SetSon(0, tab->GetContent());
}

void Pane::OnClickEvent(View* clicked_view) {
  // Note that Tab is Button which is a leaf.
  Tab* test = dynamic_cast<Tab*>(clicked_view);
  if (test) {
    SwitchTab(test);
  }
}

void Pane::AddSon(View* tab) {
  AddTab(dynamic_cast<Tab*>(tab));
  if (active_tab_ == nullptr) {
    // Note: this might cause difficulties in future.
    SwitchTab(dynamic_cast<Tab*>(tab));
  }
}

} // succotash

