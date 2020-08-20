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
  shape_.setTexture(nullptr);
  shape_.setFillColor(sf::Color::Transparent);

  Params::const_iterator it;
  if ((it = params.find("texture")) != params.end()) {
    texture_ = it->second.ToString();
  }
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

Pane::~Pane() {
  // Tabs clear content on their own.
  SetSon(content_id_, nullptr);
}

Pane::Pane(const Params& params)
    : Sprite(params) {
  Init();

  Params::const_iterator it;
  if ((it = params.find("headWeight")) != params.end()) {
    SetHeadWeight(it->second.ToFloat());
  }
}

void Pane::Init() {
  head_id_ = 0;
  content_id_ = 1;
  active_tab_ = nullptr;

  auto head = new Sprite;
  auto content = new View;

  // Head
  auto head_params = CreatePtr<LinearLayoutParams>();

  head_params->weight = 0.3;
  head->SetDispositionParams(head_params);
  head->SetLayout(CreatePtr<LinearLayout>(LinearLayout::Type::Horizontal));

  // Content
  auto content_params = CreatePtr<LinearLayoutParams>();
  content_params->weight = 1;
  content->SetDispositionParams(content_params);
  content->AddSon(new View);

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
  ((Sprite*) GetSon(0))->LoadTexture(active_tab_->texture_);
}

void Pane::SetHeadWeight(float weight) {
  auto head = GetSon(head_id_);
  LinearLayoutParamsPtr params = std::make_shared<LinearLayoutParams>(
    *std::dynamic_pointer_cast<LinearLayoutParams>(
      head->GetDispositionParams()));
  params->weight = weight;
  head->SetDispositionParams(params);
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

