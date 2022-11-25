#ifndef TEA_SCRIPTING_SCRIPTING_H
#define TEA_SCRIPTING_SCRIPTING_H

#include <memory>
#include <string>
#include <unordered_map>

#include <wren.hpp>

namespace tea {

class Engine;
class ScriptingEvents;
class Slot;

class Scripting {
public:
    explicit Scripting(Engine* engine);
    ~Scripting();

    Slot slot(int slot_index);

    [[nodiscard]] std::unique_ptr<ScriptingEvents> get_scripting_events();
private:
    static WrenBindForeignMethodFn wren_config_bindforeignmethodfn(WrenVM* wren_vm,
                                                                   const char* module,
                                                                   const char* class_name,
                                                                   bool is_static,
                                                                   const char* signature);
    static void wren_config_errorfn(WrenVM* vm, WrenErrorType error_type, const char* module, const int line, const char* msg);
    static void wren_config_writefn(WrenVM* wren_vm, const char* text);

    Engine* engine;
    WrenVM* wren_vm;

    std::unordered_map<std::string, void (*)(WrenVM*)> method_bindings;
};

}

#endif // TEA_SCRIPTING_SCRIPTING_H