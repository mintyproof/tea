#ifndef TEA_SCRIPTING_SCRIPTING_H
#define TEA_SCRIPTING_SCRIPTING_H

#include <memory>
#include <string>
#include <unordered_map>
#include <wren.hpp>

namespace tea {

class Engine;

class Scripting {
public:
    explicit Scripting(Engine* engine);
    ~Scripting();

    // on_start is absent here- on_start is the constructor of the main class, so it is automatically called.
    void on_quit();
    void on_update(double delta_time);
    void on_draw(double delta_time);

    Engine* engine; // TODO: temporary placement
private:
    static WrenForeignMethodFn wren_config_bindforeignmethodfn(WrenVM* wren_vm,
                                                               const char* module,
                                                               const char* class_name,
                                                               bool is_static,
                                                               const char* signature);
    static void wren_config_errorfn(WrenVM* vm,
                                    WrenErrorType error_type,
                                    const char* module,
                                    int line,
                                    const char* msg);
    static void wren_config_writefn(WrenVM* vm, const char* text);

    WrenVM* wren_vm;
    std::unordered_map<std::string, void (*)(WrenVM*)> method_bindings;
    WrenHandle* main_instance_handle;
    WrenHandle* on_quit_handle;
    WrenHandle* on_update_handle;
    WrenHandle* on_draw_handle;
};

}

#endif // TEA_SCRIPTING_SCRIPTING_H