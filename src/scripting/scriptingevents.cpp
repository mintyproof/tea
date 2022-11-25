#include "scripting/scriptingevents.h"

#include <wren.hpp>
#include "scripting/scripting.h"

namespace tea {

ScriptingEvents::ScriptingEvents(WrenVM* wren_vm) : wren_vm(wren_vm) {
    // fetch reusable call handles for our main instance and its event functions!
    wrenEnsureSlots(wren_vm, 1);
    wrenGetVariable(wren_vm, "tea", "Prelude__mainClassInstance", 0);

    main_instance_handle = wrenGetSlotHandle(wren_vm, 0);
    on_quit_handle   = wrenMakeCallHandle(wren_vm, "on_quit()");
    on_update_handle = wrenMakeCallHandle(wren_vm, "on_update(_)");
    on_draw_handle   = wrenMakeCallHandle(wren_vm, "on_draw(_)");
}

void ScriptingEvents::on_quit() {
    wrenEnsureSlots(wren_vm, 1);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    WrenInterpretResult _ = wrenCall(wren_vm, on_quit_handle);
}

void ScriptingEvents::on_update(double delta_time) {
    wrenEnsureSlots(wren_vm, 1);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    WrenInterpretResult _ = wrenCall(wren_vm, on_update_handle);
}

void ScriptingEvents::on_draw(double delta_time) {
    wrenEnsureSlots(wren_vm, 1);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    WrenInterpretResult _ = wrenCall(wren_vm, on_draw_handle);
}

}