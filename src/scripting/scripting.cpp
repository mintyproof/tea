#include "scripting/scripting.h"

#include <cstdio>
#include <string>
#include <wren.hpp>

#include "scripting/slot.h"

void default_write_func(WrenVM* vm, const char* text) {
    printf("%s", text);
}

void default_error_func(WrenVM* vm, WrenErrorType error_type, const char* module, const int line, const char* msg) {
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
    }
}

const char* DEBUG_SCRIPT = R"WREN(
class Tea {
    foreign static test(string)
}

class Main {
    construct on_start() {
        Tea.test("c++")
    }

    on_quit() {
    }

    on_update(dt) {
        System.print(dt)
    }

    on_draw(dt) {
    }
}

var mainClassInstance = Main.on_start()
)WREN";

void test_func(WrenVM* wren_vm) {
    const char* arg = wrenGetSlotString(wren_vm, 1);
    printf("hello %s!\n", arg);
}

WrenForeignMethodFn tea_wren_bind_foreign_method(WrenVM* wren_vm,
                                                 const char* module,
                                                 const char* class_name,
                                                 bool is_static,
                                                 const char* signature) {
    return test_func;
}

void tea_wren_bind_foreign_class() {
}

namespace tea {

Scripting::Scripting() {
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.bindForeignMethodFn = tea_wren_bind_foreign_method;
    config.bindForeignClassFn = NULL;
    config.errorFn = &default_error_func;
    config.writeFn = &default_write_func;

    wren_vm = wrenNewVM(&config);
}

Scripting::~Scripting() {
    wrenFreeVM(wren_vm);
}

Slot Scripting::slot(int slot_index) {
    wrenEnsureSlots(wren_vm, slot_index + 1);
    return { wren_vm, slot_index };
}

void Scripting::test() {
    // "static tea/Tea::test(_)"
    WrenInterpretResult result = wrenInterpret(wren_vm, "tea", DEBUG_SCRIPT);

    wrenEnsureSlots(wren_vm, 1);
    wrenGetVariable(wren_vm, "tea", "mainClassInstance", 0);
    WrenHandle* our_func = wrenGetSlotHandle(wren_vm, 0);
    WrenHandle* our_func_handle = wrenMakeCallHandle(wren_vm, "on_update(_)");

    wrenEnsureSlots(wren_vm, 2);
    wrenSetSlotHandle(wren_vm, 0, our_func);
    wrenSetSlotDouble(wren_vm, 1, 0.0);
    WrenInterpretResult other_result = wrenCall(wren_vm, our_func_handle);

    switch (result) {
    case WREN_RESULT_COMPILE_ERROR:
        printf("Compile Error!\n");
        break;
    case WREN_RESULT_RUNTIME_ERROR:
        printf("Runtime Error!\n");
        break;
    case WREN_RESULT_SUCCESS:
        printf("Success!\n");
        break;
    }
}

}