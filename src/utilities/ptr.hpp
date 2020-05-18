#ifndef PTR_HPP
#define PTR_HPP

#include <memory>


template <class T, class... Args>
std::shared_ptr<T> CreatePtr(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}


#endif // PTR_HPP

