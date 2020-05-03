#ifndef SUCCOTASH_STRINGHASHTABLE_HPP
#define SUCCOTASH_STRINGHASHTABLE_HPP

#include <unordered_map>

namespace succotash::utilities {

template <typename T>
class StringHashTable
    : public std::unordered_map<std::string, T, std::hash<std::string>,
                                std::equal_to<std::string>,
                                std::allocator<std::pair<const std::string, T>>>
{
 public:

  // Sorry, bro. This cannot be compiled :(
  // std::optional of a reference is not supported
  /*
  std::optional<T&> get(const std::string& key) const {
    auto it = this->find(key);
    if (it == this->end()) {
      return {};
    }
    return std::optional<T&>(*it);
  }
  */
};

}

#endif // SUCCOTASH_STRINGHASHTABLE_HPP
