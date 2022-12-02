#include "scripting/scripting.h"

#include <cstdio>
#include <sstream>

#include "core/engine.h"
#include "assets/assets.h"
#include "gfx/graphics.h"
#include "gfx/colour.h"

namespace tea {

Scripting::Scripting(Engine& engine) : engine(engine) {
    WrenConfiguration config;
    wrenInitConfiguration(&config);

    // so we can access the engine from anywhere we have this wren_vm, via wrenGetUserData():
    config.userData = static_cast<void*>(this);

    config.bindForeignMethodFn = [](WrenVM* wren_vm,
                                    const char* module,
                                    const char* class_name,
                                    bool is_static,
                                    const char* signature) -> WrenForeignMethodFn {
        std::ostringstream method_signature;
        if (is_static) {
            method_signature << "static ";
        }
        method_signature << module << "::" << class_name << "::" << signature;

        auto scripting = static_cast<Scripting*>(wrenGetUserData(wren_vm));

        auto entry = scripting->method_bindings.find(method_signature.str());
        if (entry != scripting->method_bindings.end()) {
            return entry->second;
        }

        return nullptr;
    };

    config.errorFn = [](WrenVM* vm, WrenErrorType error_type, const char* module, const int line, const char* msg) {
        switch (error_type) {
        case WREN_ERROR_COMPILE:
            printf("[%s line %d] [Error] %s\n", module, line, msg);
            break;
        case WREN_ERROR_STACK_TRACE:
            printf("[%s line %d] in %s\n", module, line, msg);
            break;
        case WREN_ERROR_RUNTIME:
            printf("[Runtime Error] %s\n", msg);
            break;
        default:
            break;
        }
    };

    config.writeFn = [](WrenVM* vm, const char* text) {
        printf("%s", text);
    };

    wren_vm = wrenNewVM(&config);
}

Scripting::~Scripting() {
    wrenFreeVM(wren_vm);
}

bool Scripting::init() {
    // --------------------------------------------
    // setting up prelude
    WrenInterpretResult interpret_result =
        wrenInterpret(wren_vm,
                      "tea",
                      engine.get_assets().get_string("script/prelude.wren")->c_str());
    if (interpret_result != WREN_RESULT_SUCCESS) {
        return false;
    }

    // --------------------------------------------
    // fetching reusable call handles for main instance & event functions

    wrenEnsureSlots(wren_vm, 1);
    wrenGetVariable(wren_vm, "tea", "mainClassInstance", 0);

    main_instance_handle = wrenGetSlotHandle(wren_vm, 0);
    on_quit_handle   = wrenMakeCallHandle(wren_vm, "on_quit()");
    on_update_handle = wrenMakeCallHandle(wren_vm, "on_update(_)");
    on_draw_handle   = wrenMakeCallHandle(wren_vm, "on_draw(_)");

    return true;
}

void Scripting::on_quit() {
    wrenEnsureSlots(wren_vm, 1);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    wrenCall(wren_vm, on_quit_handle);
}

void Scripting::on_update(double delta_time) {
    wrenEnsureSlots(wren_vm, 2);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    wrenSetSlotDouble(wren_vm, 1, delta_time);
    wrenCall(wren_vm, on_update_handle);
}

void Scripting::on_draw(double delta_time) {
    wrenEnsureSlots(wren_vm, 2);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    wrenSetSlotDouble(wren_vm, 1, delta_time);
    wrenCall(wren_vm, on_draw_handle);
}

Scripting* Scripting::get_from_wren_vm(WrenVM* vm) {
    return static_cast<Scripting*>(wrenGetUserData(vm));
}

}