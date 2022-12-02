#include "scripting/scripting.h"

#include <cstdio>
#include <sstream>
#include <wren.hpp>

#include "core/engine.h"
#include "assets/assets.h"

void test_func(WrenVM* wren_vm) {
    const char* arg = wrenGetSlotString(wren_vm, 1);
    printf("hello %s!\n", arg);
}

namespace tea {

Scripting::Scripting(Engine* engine) : engine(engine) {
    // --------------------------------------------
    // wren configuration

    WrenConfiguration config;
    wrenInitConfiguration(&config);

    config.userData = this; // so that we can access Scripting from anywhere we have its wren_vm, via wrenGetUserData()

    config.bindForeignMethodFn = [](WrenVM* wren_vm,
                                    const char* module,
                                    const char* class_name,
                                    bool is_static,
                                    const char* signature) -> void (*)(WrenVM*) {
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

    // --------------------------------------------
    // creating wren vm + setting up prelude

    wren_vm = wrenNewVM(&config);
    
    WrenInterpretResult interpret_result = wrenInterpret(wren_vm,
                                                         "_tea_init",
                                                         engine->get_assets().get_string("script/prelude.wren")->c_str());
    if (interpret_result != WREN_RESULT_SUCCESS) {
        exit(1);
    }

    // --------------------------------------------
    // fetching reusable call handles for main instance and event functions

    wrenEnsureSlots(wren_vm, 1);
    //wrenGetVariable(wren_vm, "tea", "Prelude__mainClassInstance", 0);

    //main_instance_handle = wrenGetSlotHandle(wren_vm, 0);
    //on_quit_handle   = wrenMakeCallHandle(wren_vm, "on_quit()");
    //on_update_handle = wrenMakeCallHandle(wren_vm, "on_update(_)");
    //on_draw_handle   = wrenMakeCallHandle(wren_vm, "on_draw(_)");

    // --------------------------------------------
    // misc ^^

    method_bindings["static tea::Tea::test(_)"] = test_func;
}

Scripting::~Scripting() {
    wrenFreeVM(wren_vm);
}

void Scripting::on_quit() {
    wrenEnsureSlots(wren_vm, 1);
    //wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    //WrenInterpretResult _ = wrenCall(wren_vm, on_quit_handle);
}

void Scripting::on_update(double delta_time) {
    wrenEnsureSlots(wren_vm, 1);
    //wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    //WrenInterpretResult _ = wrenCall(wren_vm, on_update_handle);
}

void Scripting::on_draw(double delta_time) {
    wrenEnsureSlots(wren_vm, 1);
    //wrenSetSlotHandle(wren_vm, 0, main_instance_handle);
    //WrenInterpretResult _ = wrenCall(wren_vm, on_draw_handle);
}

}