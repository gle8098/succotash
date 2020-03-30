#include "window.hpp"
#include <SFML/System.hpp>

namespace succotash {

void Window::DrawViews() { master_view_.Draw(*this); }

const View* Window::GetMasterView() const { return &master_view_; }
      View* Window::GetMasterView()       { return &master_view_; }

}  // succotash
