#ifndef SUCCOTASH_STRINGHASHTABLE_HPP
#define SUCCOTASH_STRINGHASHTABLE_HPP

#include <unordered_map>

namespace succotash::utilities {

template <typename T>
using StringHashTable = std::unordered_map<std::string, T>;

}

#endif // SUCCOTASH_STRINGHASHTABLE_HPP
