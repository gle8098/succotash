#include "Convertible.hpp"

#include <functional>
#include <stdexcept>

namespace succotash::utilities {

//------------------------------------------------------------------------------
// Local functions which are not for export
//------------------------------------------------------------------------------

inline void ThrowErrorImpl(const char* value, const char* desc) {
  char buffer[1024];
  snprintf(buffer, sizeof(buffer), "Value '%s' exception, %s", value, desc);
  throw std::runtime_error(buffer);
}

template <typename T, typename Func>
inline T ConvertStdlib(const char* value, Func func, const char* error_desc) {
  char* error;
  T result = func(value, &error);

  if (*value == '\0' || *error != '\0') {
    ThrowErrorImpl(value, error_desc);
  }

  return result;
}

//------------------------------------------------------------------------------
// Private methods
//------------------------------------------------------------------------------

void Convertible::ThrowError(const char* desc) const {
  ThrowErrorImpl(this->value_, desc);
}

//------------------------------------------------------------------------------
// Public methods
//------------------------------------------------------------------------------

Convertible::Convertible(const char* value)
 : value_(value) {
}

// String

std::string Convertible::ToString() const {
  return std::string(value_);
}

// Basic numbers

int Convertible::ToInt() const {
  return ToLong();
}

unsigned int Convertible::ToUInt() const {
  return ToULong();
}

long Convertible::ToLong() const {
  auto parser = std::bind(&strtol, std::placeholders::_1,
                          std::placeholders::_2, 0);
  return ConvertStdlib<long>(value_, parser,"couldn't convert to int/long");
}

unsigned long Convertible::ToULong() const {
  auto parser = std::bind(&strtoul, std::placeholders::_1,
                          std::placeholders::_2, 0);
  return ConvertStdlib<unsigned long>(value_, parser,
                                      "couldn't convert to uint/ulong");
}

// Numbers with floating precision

float Convertible::ToFloat() const {
  auto parser = &strtof;
  return ConvertStdlib<float>(value_, parser, "couldn't convert to float");
}

double Convertible::ToDouble() const {
  auto parser = &strtod;
  return ConvertStdlib<double>(value_, parser, "couldn't convert to double");
}

// Bool

bool Convertible::ToBool() const {
  std::string_view value(value_);
  if (value == "true" || value == "True") {
    return true;
  } else if (value == "false" || value == "False") {
    return false;
  } else {
    ThrowError("couldn't convert to bool");
    return false;
  }
}

// Operators

bool Convertible::operator==(const std::string& rhs) const {
  return rhs == value_;
}

} // namespace succotash::utilities
