#include "scripting/scripting.h"

// TODO: this is just here temporarily
#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(tea);

std::string get_res_string(std::string filename) {
    auto res_fs = cmrc::tea::get_filesystem();
    auto file = res_fs.open(filename);

    std::string out;
    out.insert(out.begin(), file.begin(), file.end());

    std::ifstream stream;
    stream.open(filename, std::ifstream::in | std::ifstream::binary);

    out.insert(out.begin(), (std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    return out;
}

#include <cstdio>
#include <sstream>
#include <wren.hpp>

#include "core/engine.h"
#include "scripting/scriptingevents.h"
#include "scripting/slot.h"

void test_func(WrenVM* wren_vm) {
    const char* arg = wrenGetSlotString(wren_vm, 1);
    printf("hello %s!\n", arg);
}

namespace tea {

Scripting::Scripting(Engine* engine) : engine(engine) {
    WrenConfiguration config;
    wrenInitConfiguration(&config);

    config.userData = this; // so that we can access Scripting from anywhere we have its wren_vm, via wrenGetUserData()

    config.bindForeignMethodFn = wren_config_bindforeignmethodfn;
    config.errorFn = wren_config_errorfn;
    config.writeFn = wren_config_writefn;

    method_bindings["static tea::Tea::test(_)"] = test_func;

    wren_vm = wrenNewVM(&config);

    //WrenInterpretResult interpret_result = wrenInterpret(wren_vm, "_tea_init", get_res_string("script/prelude.wren").c_str());
    //if (interpret_result != WREN_RESULT_SUCCESS) {
    //    exit(1);
    //}
}

Scripting::~Scripting() {
    wrenFreeVM(wren_vm);
}

Slot Scripting::slot(int slot_index) {
    wrenEnsureSlots(wren_vm, slot_index + 1);
    return { wren_vm, slot_index };
}

std::unique_ptr<ScriptingEvents> Scripting::get_scripting_events() {
    return std::make_unique<ScriptingEvents>(wren_vm);
}

WrenBindForeignMethodFn Scripting::wren_config_bindforeignmethodfn(WrenVM* wren_vm,
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
}

void Scripting::wren_config_errorfn(WrenVM* vm, WrenErrorType error_type, const char* module, const int line, const char* msg) {
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
}

void Scripting::wren_config_writefn(WrenVM* wren_vm, const char* text) {
    printf("%s", text);
}

}