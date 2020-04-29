#include "Convertible.hpp"

#include <cstring>
#include <functional>
#include <stdexcept>

namespace succotash::utilities {

// Private methods

inline void ThrowErrorImpl(const char* value, const char* desc) {
  char buffer[1024];
  snprintf(buffer, sizeof(buffer), "Value '%s' exception, %s", value, desc);
  throw std::runtime_error(buffer);
}

void Convertible::ThrowError(const char* desc) const {
  ThrowErrorImpl(this->value_, desc);
}

template <typename T, typename Func>
inline T ConvertStdlib(const char* value, Func func, const char* error_desc) {
  char* error;
  long result = func(value, &error);

  if (*value == '\0' || *error != '\0') {
    ThrowErrorImpl(value, error_desc);
  }

  return result;
}

// Public methods

Convertible::Convertible(const char* value)
 : value_(value) {
}

std::string Convertible::ToString() const {
  return std::string(value_);
}

int Convertible::ToInt() const {
  return ToLong();
}

unsigned int Convertible::ToUInt() const {
  return ToULong();
}

long Convertible::ToLong() const {
  return ConvertStdlib<long>(value_,
                             std::bind(&strtol, std::placeholders::_1, std::placeholders::_2, 0),
                             "couldn't convert to int/long");
}

unsigned long Convertible::ToULong() const {
  return ConvertStdlib<unsigned long>(value_,
                                      std::bind(&strtoul, std::placeholders::_1, std::placeholders::_2, 0),
                                      "couldn't convert to uint/ulong");
}

bool Convertible::ToBool() const {
  if (strcmp(value_, "true") == 0 || strcmp(value_, "True") == 0) {
    return true;
  } else if (strcmp(value_, "false") == 0 || strcmp(value_, "False") == 0) {
    return false;
  } else {
    ThrowError("couldn't convert to bool");
    return false;
  }
}

bool Convertible::operator==(const std::string& rhs) const {
  return rhs == value_;
}

} // namespace succotash::utilities