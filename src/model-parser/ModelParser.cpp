#include "ModelParser.hpp"

#include <StringHashTable.hpp>
#include <cstdarg>
#include <cstring>
#include <fstream>
#include <pugixml.hpp>

#include "ParsingObjects.hpp"

namespace succotash::xml {

ParseException::ParseException(const std::string& description)
    : runtime_error(description) {
}

std::string ReadWholeFile(const std::string& filepath) {
  std::ifstream stream(filepath);
  stream.seekg(0, std::ios::end);
  size_t size = stream.tellg();
  stream.seekg(0);

  std::string buffer(size, 0);
  stream.read(&buffer[0], size);
  return buffer;
}

struct Parser {
  explicit Parser(const std::string& filepath)
    : filepath_(filepath) {
  }

  View* ParseModel() {
    file_content_ = ReadWholeFile(filepath_);

    pugi::xml_document doc;
    auto parse_result = doc.load_buffer(file_content_.data(), file_content_.size());
    if (!parse_result) {
      throw ParseException(parse_result.description());
    }

    return ParseModelRecursive(doc.document_element());
  }

 private:
  View* ParseModelRecursive(const pugi::xml_node& tag) {
    auto view_fact_it = kViewFactories.find(tag.name());
    if (view_fact_it == kViewFactories.end()) {
      ThrowParseException(tag.offset_debug(), "View class was not found");
    }
    ObjectFactory<View> view_factory = view_fact_it->second;

    StringHashTable<pugi::xml_attribute> view_params;
    StringHashTable<pugi::xml_attribute> layout_params;
    StringHashTable<std::string> parent_params;
    ObjectFactory<Layout> layout_factory = nullptr;

    for (auto attr : tag.attributes()) {
      std::string name = attr.name();

      if (name.rfind("layout:", 0) == 0) {
        std::string key = name.substr(strlen("layout:"));
        layout_params[key] = attr;

      } else if (name.rfind("layout", 0) == 0) {
        auto layout_fact_it = kLayoutFactories.find(attr.value());
        if (layout_fact_it == kLayoutFactories.end()) {
          ThrowParseException(tag.offset_debug(), "Layout class was not found");
        }
        layout_factory = layout_fact_it->second;

      } else if (name.rfind("parent:", 0) == 0) {
        std::string key = name.substr(strlen("parent:"));
        parent_params[key] = attr.value();

      } else if (name.find(':') == std::string::npos) {
        view_params[name] = attr;

      } else if (name.rfind("xmlns:", 0) != 0) {
        // This is not from above and not xmlns namespace... than what is it?
        ThrowParseException(tag.offset_debug(), "Unknown namespace %s", name.c_str());
      }
    }

    View* view = view_factory(view_params);
    Layout* layout = layout_factory ? layout_factory(layout_params) : nullptr;

    view->SetLayout(layout);
    view->SetParentLayoutParams(parent_params);

    for (auto child : tag.children()) {
      View* son = ParseModelRecursive(child);
      view->AddSon(son);
    }

    return view;
  }

  void ThrowParseException(ptrdiff_t offset, const char* description, ...) {
    char desc_buffer[1024];
    int buf_offset = 0;

    buf_offset += snprintf(desc_buffer, sizeof(desc_buffer), "[at %s : offset %ld] ", filepath_.c_str(), offset);

    // Call vsnprintf
    va_list argptr;
    va_start(argptr, description);
    vsnprintf(desc_buffer + buf_offset, sizeof(desc_buffer) - buf_offset, description, argptr);
    va_end(argptr);

    throw ParseException(desc_buffer);
  }

 private:
  const std::string& filepath_;
  std::string        file_content_;
};

View* ParseModel(const std::string& filepath) {
  Parser parser(filepath);
  return parser.ParseModel();
}

} // namespace succotash