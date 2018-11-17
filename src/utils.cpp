#include "utils.h"

#include <sstream>

namespace Tea {
    void (*Tea::ScriptingBinder::resolve_function(bool        is_static,
                                                  std::string module,
                                                  std::string className,
                                                  std::string signature))(WrenVM*) {
        std::ostringstream full_signature;

        if (is_static) full_signature << "static ";
        full_signature << module << "::" << className << "::" << signature;

        auto found_function = this->methods.find(full_signature.str());
        if (found_function == this->methods.end()) return nullptr;
        return found_function->second;
    }

    void Tea::ScriptingBinder::bind_method(std::string signature, void (*fn)(WrenVM*)) {
        this->methods.emplace(signature, fn);
    }
}