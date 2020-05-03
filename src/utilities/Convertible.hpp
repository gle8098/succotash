#ifndef SUCCOTASH_CONVERTIBLE_HPP
#define SUCCOTASH_CONVERTIBLE_HPP

#include <string>

namespace succotash::utilities {

// Construct this class over a c-string and convert it to any primitive.
//
// Note that Convertible doesn't own passed string, so ensure it is available
// until Convertible is not destroyed.
//
// Note that all methods can throw std::runtime_error if string cannot be
// converted to wished type.

struct Convertible {
  Convertible(const char* value);

  // String
  std::string ToString() const;

  // Basic numbers
  int ToInt() const;
  unsigned int ToUInt() const;
  long ToLong() const;
  unsigned long ToULong() const;

  // Numbers with floating precision
  float ToFloat() const;
  double ToDouble() const;

  // Bool
  bool ToBool() const;

  // Compare with string
  bool operator==(const std::string& rhs) const;

 private:
  void ThrowError(const char* desc) const;

 private:
  const char* value_;
};

} // namespace succotash::utilities

#endif  // SUCCOTASH_CONVERTIBLE_HPP
