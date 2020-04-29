#ifndef SUCCOTASH_CONVERTIBLE_HPP
#define SUCCOTASH_CONVERTIBLE_HPP

#include <string>
namespace succotash::utilities {

struct Convertible {
  Convertible(const char* value);

  // String
  std::string ToString() const;

  // Basic numbers
  int ToInt() const;
  unsigned int ToUInt() const;
  long ToLong() const;
  unsigned long ToULong() const;

  // Bool
  bool ToBool() const;

  // Compare with string
  bool operator==(const std::string& rhs) const;
 private:
  void ThrowError(const char* desc) const;

  const char* value_;
};

} // namespace succotash::utilities

#endif  // SUCCOTASH_CONVERTIBLE_HPP
