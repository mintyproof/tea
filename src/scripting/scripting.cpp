#include "scripting/scripting.h"

#include <cstdio>
#include <wren.hpp>

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
var say_hello_to = Fn.new { |name|
    System.print("hello %(name)!")
}

say_hello_to.call("tea")
)WREN";

namespace tea {

Scripting::Scripting() {
    WrenConfiguration config;
    wrenInitConfiguration(&config);
    config.errorFn = &default_error_func;
    config.writeFn = &default_write_func;

    wren_vm = wrenNewVM(&config);
}

Scripting::~Scripting() {
    wrenFreeVM(wren_vm);
}

void Scripting::test() {
    WrenInterpretResult result = wrenInterpret(wren_vm, "tea", DEBUG_SCRIPT);

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