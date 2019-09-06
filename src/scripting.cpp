#include "scripting.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <typeindex>

#include <wren.hpp>

#include "engine.h"

namespace Tea {
    bool Slot::is_num() const { return wrenGetSlotType(this->vm, this->index) == WREN_TYPE_NUM; }

    double Slot::as_num() const {
        if (!this->is_num()) throw std::runtime_error("uwu");
        return wrenGetSlotDouble(this->vm, this->index);
    }

    void Slot::set_num(double new_num) { wrenSetSlotDouble(this->vm, this->index, new_num); }

    bool Slot::is_str() const { return wrenGetSlotType(this->vm, this->index) == WREN_TYPE_STRING; }

    std::string Slot::as_str() const {
        if (!this->is_str()) throw std::runtime_error("uwu");
        return wrenGetSlotString(this->vm, this->index);
    }

    void Slot::set_str(std::string&& new_str) { wrenSetSlotString(this->vm, this->index, new_str.c_str()); }

    bool Slot::is_bool() const { return wrenGetSlotType(this->vm, this->index) == WREN_TYPE_BOOL; }

    bool Slot::as_bool() const {
        if (!this->is_bool()) throw std::runtime_error("uwu");
        return wrenGetSlotBool(this->vm, this->index);
    }

    void Slot::set_bool(bool new_bool) { wrenSetSlotBool(this->vm, this->index, new_bool); }

    bool Slot::is_null() const { return wrenGetSlotType(this->vm, this->index) == WREN_TYPE_NULL; }

    void Slot::set_null() { wrenSetSlotNull(this->vm, this->index); }

    bool Slot::_is_type(const std::type_info& type) const {
        if (wrenGetSlotType(this->vm, this->index) != WREN_TYPE_FOREIGN) {
            return false;
        }

        auto ptr = wrenGetSlotForeign(this->vm, this->index);
        auto wrapper = static_cast<ForeignWrapper<char>*>(ptr);
        return wrapper->type == std::type_index(type);
    }

    void* Slot::_get_foreign() const { return wrenGetSlotForeign(this->vm, this->index); }

    void* Slot::_set_foreign(uint8_t class_slot, size_t size) {
        return wrenSetSlotNewForeign(this->vm, this->index, class_slot, size);
    }

    Scripting::Scripting(Engine& engine): engine(engine) {
        std::cout << "Initializing scripting engine: Wren " << WREN_VERSION_STRING << std::endl;

        WrenConfiguration cfg;
        wrenInitConfiguration(&cfg);

        cfg.userData = static_cast<void*>(this);
        cfg.writeFn = [](WrenVM*, const char* str) { std::cout << str << std::flush; };
        cfg.errorFn = [](WrenVM*, WrenErrorType type, const char* module, int line, const char* message) {
            if (type == WrenErrorType::WREN_ERROR_COMPILE) {
                std::cerr << "Compilation error (" << module << "@" << line << "): " << message << std::endl;
            } else if (type == WrenErrorType::WREN_ERROR_RUNTIME) {
                std::cerr << "Runtime error: " << message << std::endl;
            } else if (type == WrenErrorType::WREN_ERROR_STACK_TRACE) {
                std::cerr << "    at " << module << "@" << line << ": " << message << std::endl;
            }
        };
        cfg.loadModuleFn = [](WrenVM* vm, const char* name) -> char* {
            auto scripting = static_cast<Scripting*>(wrenGetUserData(vm));
            auto& engine = scripting->get_engine();

            std::ostringstream filename;
            filename << name << ".wren";

            std::vector<uint8_t> data;
            if (!engine.get_assets().load_raw(filename.str(), data)) return nullptr;

            // Using C strings here because Wren expects a malloc()'d char* for it to take ownership of
            char* code = static_cast<char*>(malloc(data.size() + 1));
            memcpy(code, &data.front(), data.size());
            code[data.size()] = '\0';

            return code;
        };
        cfg.bindForeignMethodFn = [](WrenVM* vm,
                                     const char* module,
                                     const char* className,
                                     bool isStatic,
                                     const char* signature) -> void (*)(WrenVM*) {
            std::ostringstream full_signature;
            if (isStatic) full_signature << "static ";
            full_signature << module << "::" << className << "::" << signature;

            auto scripting = static_cast<Scripting*>(wrenGetUserData(vm));
            auto entry = scripting->methods.find(full_signature.str());
            if (entry != scripting->methods.end()) {
                return entry->second;
            }
            return nullptr;
        };

        this->vm = wrenNewVM(&cfg);
    }

    Scripting::~Scripting() { wrenFreeVM(this->vm); }

    Scripting* Scripting::_from_vm_ptr(WrenVM* ptr) { return static_cast<Scripting*>(wrenGetUserData(ptr)); }

    Engine& Scripting::get_engine() { return this->engine; }

    Slot Scripting::slot(uint8_t slot_index) {
        wrenEnsureSlots(this->vm, slot_index + 1);
        return Slot(this->vm, slot_index);
    }

    void Scripting::error(std::string err) {
        wrenSetSlotString(vm, 0, err.c_str());
        wrenAbortFiber(vm, 0);
    }

    void Scripting::init(std::string main_module, std::string main_class) {
        // Run the prelude with the main class
        // TODO: make "main::Main" configurable here
        std::ostringstream exec_prelude_code;
        exec_prelude_code << "import \"tea/prelude\" for Prelude\n";
        exec_prelude_code << "import \"" << main_module << "\" for " << main_class << "\n";
        exec_prelude_code << "Prelude.run(" << main_class << ")";

        auto interpret_result = wrenInterpret(this->vm, "_init", exec_prelude_code.str().c_str());
        if (interpret_result != WrenInterpretResult::WREN_RESULT_SUCCESS) {
            exit(1);
        }

        // Then get a reusable call handle for Prelude::update that we can use
        wrenEnsureSlots(this->vm, 1);
        wrenGetVariable(this->vm, "tea/prelude", "Prelude", 0);
        this->prelude_class_handle = wrenGetSlotHandle(this->vm, 0);
        this->prelude_update_method_handle = wrenMakeCallHandle(this->vm, "update(_)");
    }

    void Scripting::update(double delta) {
        // Call the update method in Prelude
        wrenEnsureSlots(this->vm, 2);
        wrenSetSlotHandle(this->vm, 0, this->prelude_class_handle);
        wrenSetSlotDouble(this->vm, 1, delta);
        wrenCall(this->vm, this->prelude_update_method_handle);
    }

    void Scripting::_bind(std::string signature, void (*func)(WrenVM*)) { this->methods.emplace(signature, func); }
}