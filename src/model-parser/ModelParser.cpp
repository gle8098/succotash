#include "ModelParser.hpp"

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
  View* ParseModelRecursive(const pugi::xml_node& tag, const ObjectFactory<LayoutParams>* params_factory = nullptr) {
    auto view_fact_it = view_factories.find(tag.name());
    if (view_fact_it == view_factories.end()) {
      ThrowParseException(tag.offset_debug(), "View class was not found");
    }
    ObjectFactory<View>& view_factory = view_fact_it->second;

    StringHashTable<Convertible> view_params;
    StringHashTable<Convertible> layout_params;
    StringHashTable<Convertible> parent_params;
    ObjectFactory<Layout> layout_factory = nullptr;
    ObjectFactory<LayoutParams> my_params_factory = nullptr;

    for (auto attr : tag.attributes()) {
      std::string name = attr.name();

      if (name.rfind("layout:", 0) == 0) {
        std::string key = name.substr(strlen("layout:"));
        layout_params.emplace(key, attr.value());

      } else if (name.rfind("layout", 0) == 0) {
        auto layout_fact_it = layout_factories.find(attr.value());
        if (layout_fact_it == layout_factories.end()) {
          ThrowParseException(tag.offset_debug(), "Layout class was not found");
        }
        auto factories = layout_fact_it->second;
        layout_factory = factories.layout_factory;
        my_params_factory = factories.params_factory;

      } else if (name.rfind("parent:", 0) == 0) {
        std::string key = name.substr(strlen("parent:"));
        parent_params.emplace(key, attr.value());

      } else if (name.find(':') == std::string::npos) {
        view_params.emplace(name, attr.value());

      } else if (name.rfind("xmlns:", 0) != 0) {
        // This is not from above and not xmlns namespace... than what is it?
        ThrowParseException(tag.offset_debug(), "Unknown namespace %s", name.c_str());
      }
    }

    View* view = nullptr;
    Layout* layout = nullptr;
    LayoutParams* params = nullptr;

    try {
      view = view_factory(view_params);
      layout = layout_factory ? ( layout_factory)(layout_params) : nullptr;
      params = params_factory ? (*params_factory)(parent_params) : nullptr;
    } catch (std::exception& ex) {
      ThrowParseException(tag.offset_debug(), ex.what());
    }

    view->SetLayout(layout);
    view->SetDispositionParams(params);

    for (auto child : tag.children()) {
      View* son = ParseModelRecursive(child, &my_params_factory);
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