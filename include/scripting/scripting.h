#ifndef TEA_SCRIPTING_SCRIPTING_H
#define TEA_SCRIPTING_SCRIPTING_H

#include <memory>
#include <string>
#include <unordered_map>

struct WrenVM;
struct WrenHandle;

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
private:
    Engine* engine;
    WrenVM* wren_vm;
    std::unordered_map<std::string, void (*)(WrenVM*)> method_bindings;
    WrenHandle* main_instance_handle;
    WrenHandle* on_quit_handle;
    WrenHandle* on_update_handle;
    WrenHandle* on_draw_handle;
};

}

#endif // TEA_SCRIPTING_SCRIPTING_H