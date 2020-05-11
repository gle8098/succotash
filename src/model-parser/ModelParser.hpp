#ifndef SUCCOTASH_MODELPARSER_HPP
#define SUCCOTASH_MODELPARSER_HPP

#include <pugixml.hpp>
#include <string_view>

#include "../view.hpp"

namespace succotash::xml {

struct ParseException : std::runtime_error {
  ParseException(const std::string& description);
};

ViewPtr ParseModel(const std::string& filepath);

}  // namespace succotash::xml

#endif // SUCCOTASH_MODELPARSER_HPP
