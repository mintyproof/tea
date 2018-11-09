#include <functional>
#include <string>
#include <unordered_map>

typedef struct WrenVM WrenVM;

namespace Tea {
    class ScriptingBinder {
    public:
        void (*resolve_function(bool is_static, std::string module, std::string className, std::string signature))(
            WrenVM*);

        void bind_method(std::string signature, void (*fn)(WrenVM*));

    private:
        std::unordered_map<std::string, void (*)(WrenVM*)> methods;
    };
}