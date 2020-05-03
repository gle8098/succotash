#include "ModelParser.hpp"

#include <cstdarg>
#include <cstring>
#include <fstream>
#include <pugixml.hpp>

#include "ParsingObjects.hpp"

namespace succotash::xml {

//------------------------------------------------------------------------------
// Parser utilities functions
//------------------------------------------------------------------------------

std::string ReadWholeFile(const std::string& filepath) {
  std::ifstream stream(filepath);
  stream.seekg(0, std::ios::end);
  size_t size = stream.tellg();
  stream.seekg(0);

  std::string buffer(size, 0);
  stream.read(&buffer[0], size);
  return buffer;
}

// std::string utils
#define STARTS_WITH(string, substring) ((string).rfind(substring, 0) == 0)
#define NOT_CONTAINS(the_str, substr) ((the_str).find(substr) == std::string::npos)

//------------------------------------------------------------------------------
// Parser error messages
//------------------------------------------------------------------------------

const char* ERROR_PREFIX           = "Tag '%s':%d:%d. ";
const char* ERROR_VIEW_NOT_FOUND   = "View class '%s' was not found";
const char* ERROR_LAYOUT_NOT_FOUND = "Layout class '%s' was not found";
const char* ERROR_UNKNOWN_NS       = "Unknown namespace %s";

//------------------------------------------------------------------------------
// class Parser definition
//------------------------------------------------------------------------------

struct Parser {
  explicit Parser(const std::string& filepath);
  View* ParseModel();

 private:
  // Function that recursively parses `tag` subtree of View.
  // params_factory is factory for parent's Layout parameters
  View* ParseModelRecursive(const pugi::xml_node& tag,
                            const ObjectFactory<LayoutParams>* params_factory
                                = nullptr);

  // Throws an instance of ParseException.
  // offset is returned by pugi::xml_node::ofset_debug().
  // Note that this function works like printf. I.e. description and all varargs
  // are passed to appropriate printf function.
  void ThrowException(ptrdiff_t offset, const char* description, ...);

  struct RowAndCol {
    int row;
    int col;
  };

  // By `offset` finds and returns row and column numbers of the referred
  // character.
  RowAndCol GetRowAndColByOffset(ptrdiff_t offset);

 private:
  const std::string& filepath_;
  std::string        file_content_;
};

//------------------------------------------------------------------------------
// Implementation of exporting method from .hpp file
//------------------------------------------------------------------------------

ParseException::ParseException(const std::string& description)
    : runtime_error(description) {
}

View* ParseModel(const std::string& filepath) {
  Parser parser(filepath);
  return parser.ParseModel();
}

//------------------------------------------------------------------------------
// class Parser implementation
//------------------------------------------------------------------------------

Parser::Parser(const std::string& filepath)
    : filepath_(filepath) {
}

View* Parser::ParseModel() {
  file_content_ = ReadWholeFile(filepath_);

  pugi::xml_document doc;
  auto parse_result = doc.load_buffer(file_content_.data(),
                                      file_content_.size());
  if (!parse_result) {
    throw ParseException(parse_result.description());
  }

  return ParseModelRecursive(doc.document_element());
}

View* Parser::ParseModelRecursive(const pugi::xml_node& tag,
                                  const ObjectFactory<LayoutParams>*
                                      params_factory) {
  // 1. Recognize View
  auto view_fact_it = view_factories.find(tag.name());
  if (view_fact_it == view_factories.end()) {
    ThrowException(tag.offset_debug(), ERROR_VIEW_NOT_FOUND, tag.name());
  }
  ObjectFactory<View>& view_factory = view_fact_it->second;

  // 1b. Define most of the variables
  StringHashTable<Convertible> view_params;
  StringHashTable<Convertible> layout_params;
  StringHashTable<Convertible> parent_params;
  ObjectFactory<Layout> layout_factory = nullptr;
  ObjectFactory<LayoutParams> my_params_factory = nullptr;

  // 2. Recognize attributes
  for (auto attr : tag.attributes()) {
    std::string name = attr.name();

    if (STARTS_WITH(name, "layout:")) {
      std::string key = name.substr(strlen("layout:"));
      layout_params.emplace(key, attr.value());

    } else if (STARTS_WITH(name, "layout")) {
      auto factories_it = layout_factories.find(attr.value());
      if (factories_it == layout_factories.end()) {
        ThrowException(tag.offset_debug(), ERROR_LAYOUT_NOT_FOUND,
                       attr.value());
      }
      layout_factory = factories_it->second.layout_factory;
      my_params_factory = factories_it->second.params_factory;

    } else if (STARTS_WITH(name, "parent:")) {
      std::string key = name.substr(strlen("parent:"));
      parent_params.emplace(key, attr.value());

    } else if (NOT_CONTAINS(name, '.')) {
      view_params.emplace(name, attr.value());

    } else if (!STARTS_WITH(name, "xmlns:")) {
      // This is not from above and not xmlns namespace... than what is it?
      ThrowException(tag.offset_debug(), ERROR_UNKNOWN_NS, name.c_str());
    }
  }

  // 3. Call the factories & set everything up
  View* view = nullptr;
  Layout* layout = nullptr;
  LayoutParams* params = nullptr;

  try {
    view = view_factory(view_params);
    layout = layout_factory ? ( layout_factory)(layout_params) : nullptr;
    params = params_factory ? (*params_factory)(parent_params) : nullptr;
  } catch (std::exception& ex) {
    ThrowException(tag.offset_debug(), ex.what());
  }

  view->SetLayout(layout);
  view->SetDispositionParams(params);

  // 4.
  for (auto child : tag.children()) {
    View* son = ParseModelRecursive(child, &my_params_factory);
    view->AddSon(son);
  }

  return view;
}

void Parser::ThrowException(ptrdiff_t offset, const char* description,
                                 ...) {
  char desc_buffer[1024];
  int buf_offset = 0;

  RowAndCol error_loc = GetRowAndColByOffset(offset);
  buf_offset += snprintf(desc_buffer, sizeof(desc_buffer), ERROR_PREFIX,
                         filepath_.c_str(), error_loc.row, error_loc.col);

  /* Call to vsnprintf */
  va_list argptr;
  va_start(argptr, description);
  vsnprintf(desc_buffer + buf_offset, sizeof(desc_buffer) - buf_offset,
            description, argptr);
  va_end(argptr);
  /* Call end */

  throw ParseException(desc_buffer);
}

Parser::RowAndCol Parser::GetRowAndColByOffset(ptrdiff_t offset) {
  const char* cur_ptr = file_content_.c_str();
  const char* end_ptr = cur_ptr + offset;
  RowAndCol parsed = { .row = 1, .col = 0 };

  const char* line_start = cur_ptr;
  const char* found = {};
  while ( (found = strchr(line_start, '\n')) != NULL && found < end_ptr ) {
    ++parsed.row;
    line_start = found + 1;
  }
  parsed.col = end_ptr - line_start + 1;
  return parsed;
}

} // namespace succotash
