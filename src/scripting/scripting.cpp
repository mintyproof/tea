#include "scripting/scripting.h"

#include <cstdio>
#include <sstream>

#include "core/engine.h"
#include "assets/assets.h"
#include "gfx/graphics.h"
#include "gfx/colour.h"
void test_func(WrenVM* wren_vm) {
    const char* arg = wrenGetSlotString(wren_vm, 1);
    printf("hello %s!\n", arg);
}

void clear_to_colour(WrenVM* wren_vm) {
    double r = wrenGetSlotDouble(wren_vm, 1);
    double g = wrenGetSlotDouble(wren_vm, 2);
    double b = wrenGetSlotDouble(wren_vm, 3);

    static_cast<tea::Scripting*>(wrenGetUserData(wren_vm))->engine->get_graphics().clear_to_colour(tea::ColourRGB(r, g, b));
}

namespace tea {

Scripting::Scripting(Engine* engine) : engine(engine) {
    method_bindings["static tea::Tea::test(_)"] = test_func;
    method_bindings["static tea::Tea::clear_to_colour(_,_,_)"] = clear_to_colour;

    // --------------------------------------------
    // wren configuration

    WrenConfiguration config;
    wrenInitConfiguration(&config);

    // so we can access scripting (and thus engine) from anywhere we have this wren_vm, via wrenGetUserData():
    config.userData = static_cast<void*>(this);
    config.bindForeignMethodFn = Scripting::wren_config_bindforeignmethodfn;
    config.errorFn = Scripting::wren_config_errorfn;
    config.writeFn = Scripting::wren_config_writefn;

    // --------------------------------------------
    // creating wren vm + setting up prelude

    wren_vm = wrenNewVM(&config);

    WrenInterpretResult interpret_result =
        wrenInterpret(wren_vm,
                      "tea",
                      engine->get_assets().get_string("script/prelude.wren")->c_str());
    if (interpret_result != WREN_RESULT_SUCCESS) {
        exit(1);
    }

    // --------------------------------------------
    // fetching reusable call handles for main instance and event functions

    wrenEnsureSlots(wren_vm, 1);
    wrenGetVariable(wren_vm, "tea", "mainClassInstance", 0);

    main_instance_handle = wrenGetSlotHandle(wren_vm, 0);
    on_quit_handle   = wrenMakeCallHandle(wren_vm, "on_quit()");
    on_update_handle = wrenMakeCallHandle(wren_vm, "on_update(_)");
    on_draw_handle   = wrenMakeCallHandle(wren_vm, "on_draw(_)");

    // --------------------------------------------
    // misc ^^

}

Scripting::~Scripting() {
    wrenFreeVM(wren_vm);
}

void Scripting::on_quit() {
    wrenEnsureSlots(wren_vm, 1);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    WrenInterpretResult _ = wrenCall(wren_vm, on_quit_handle);
}

void Scripting::on_update(double delta_time) {
    wrenEnsureSlots(wren_vm, 2);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    wrenSetSlotDouble(wren_vm, 1, delta_time);
    WrenInterpretResult _ = wrenCall(wren_vm, on_update_handle);
}

void Scripting::on_draw(double delta_time) {
    wrenEnsureSlots(wren_vm, 2);
    wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    wrenSetSlotDouble(wren_vm, 1, delta_time);
    WrenInterpretResult _ = wrenCall(wren_vm, on_draw_handle);
}


WrenForeignMethodFn Scripting::wren_config_bindforeignmethodfn(WrenVM* wren_vm,
                                                    const char* module,
                                                    const char* class_name,
                                                    bool is_static,
                                                    const char* signature) {
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

void Scripting::wren_config_errorfn(WrenVM* vm,
                                    WrenErrorType error_type,
                                    const char* module,
                                    const int line,
                                    const char* msg) {
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

void Scripting::wren_config_writefn(WrenVM* vm, const char* text) {
    printf("%s", text);
};

}