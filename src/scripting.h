#ifndef TEA_SCRIPTING_H
#define TEA_SCRIPTING_H

#include <cstdint>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

struct WrenVM;
struct WrenHandle;

namespace Tea {
    class Engine;

    template <class T>
    struct ForeignWrapper {
        std::type_index type;
        T               value;
    };

    class Slot {
        friend class Scripting;

    public:
        bool        is_num() const;
        double      as_num() const;
        void        set_num(double new_num);
        bool        is_str() const;
        std::string as_str() const;
        void        set_str(std::string&& new_str);
        bool        is_bool() const;
        bool        as_bool() const;
        void        set_bool(bool new_bool);
        bool        is_null() const;
        void        set_null();

        template <class T>
        bool is_native_type() const {
            auto ptr = static_cast<ForeignWrapper<T>*>(this->_get_foreign());
            return ptr->type == std::type_index(typeid(T));
        }

        template <class T>
        T& get_native_type() const {
            if (!this->is_native_type<T>()) {
                throw std::runtime_error("uwu");
            }
            auto ptr = static_cast<ForeignWrapper<T>*>(this->_get_foreign());
            return ptr->value;
        }

        template <class T>
        T& set_native_type(T&& new_value, uint8_t slot_containing_class) {
            auto ptr =
                static_cast<ForeignWrapper<T>*>(this->_set_foreign(slot_containing_class, sizeof(ForeignWrapper<T>)));
            ptr->type  = std::type_index(typeid(T));
            ptr->value = new_value;
            return ptr->value;
        }

    private:
        Slot(WrenVM* vm, uint8_t index): vm(vm), index(index) {}

        bool  _is_type(const std::type_info& type) const;
        void* _get_foreign() const;
        void* _set_foreign(uint8_t class_slot, size_t size);

        WrenVM* vm;
        uint8_t index;
    };

    class Scripting {
    public:
        Scripting(Engine& engine);
        Scripting(const Scripting&) = delete;
        Scripting& operator=(const Scripting&) = delete;
        ~Scripting();

        Engine& get_engine();

        Slot slot(uint8_t slot_index);
        void error(std::string err);

        template <typename F>
        void bind(std::string signature, F callback) {
            static auto mb    = callback;
            static auto inner = [](WrenVM* vm) {
                Scripting* s = Scripting::_from_vm_ptr(vm);
                mb(*s);
            };

            this->_bind(signature, inner);
        }

        void init(std::string main_module, std::string main_class);
        void update(double delta);

    private:
        void              _bind(std::string signature, void (*func)(WrenVM*));
        static Scripting* _from_vm_ptr(WrenVM* ptr);

        std::unordered_map<std::string, void (*)(WrenVM*)> methods;
        Engine&                                            engine;
        WrenVM*                                            vm;

        WrenHandle* prelude_class_handle;
        WrenHandle* prelude_update_method_handle;
    };
}

#endif