#ifndef TEA_SCRIPTING_SCRIPTING_H
#define TEA_SCRIPTING_SCRIPTING_H

#include <memory>
#include <string>
#include <unordered_map>
#include <wren.hpp>

#include "core/engine.h"

namespace tea {

class Engine;
class Context;

class Scripting {
public:
    explicit Scripting(Engine& engine);
    ~Scripting();

    bool init();

    template <typename F>
    void bind(const std::string& signature, F callback) {
        static auto binding_method = callback;
        static auto inner = [](WrenVM* vm) {
            Context context = Scripting::get_from_wren_vm(vm)->engine.get_context();
            binding_method(vm, context);
        };

        this->method_bindings[signature] = inner;
    }

    // on_start is absent here- on_start is the constructor of the main class, so it is automatically called.
    void on_quit();
    void on_update(double delta_time);
    void on_draw(double delta_time);
private:
    static Scripting* get_from_wren_vm(WrenVM* vm);

    WrenVM* wren_vm;
    Engine& engine;

    std::unordered_map<std::string, void (*)(WrenVM*)> method_bindings;
    WrenHandle* main_instance_handle;
    WrenHandle* on_quit_handle;
    WrenHandle* on_update_handle;
    WrenHandle* on_draw_handle;
};

}

#endif // TEA_SCRIPTING_SCRIPTING_H