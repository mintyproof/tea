#ifndef TEA_SCRIPTING_SCRIPTINGEVENTS_H
#define TEA_SCRIPTING_SCRIPTINGEVENTS_H

#include <memory>

struct WrenVM;
struct WrenHandle;

namespace tea {

class ScriptingEvents {
public:
    explicit ScriptingEvents(WrenVM* wren_vm);

    // on_start is absent here- on_start is the constructor of the main class, so it is automatically called.
    void on_quit();
    void on_update(double delta_time);
    void on_draw(double delta_time);
private:
    WrenVM* wren_vm;
    WrenHandle* main_instance_handle;
    WrenHandle* on_quit_handle;
    WrenHandle* on_update_handle;
    WrenHandle* on_draw_handle;
};

}

#endif // TEA_SCRIPTING_SCRIPTINGEVENTS_H