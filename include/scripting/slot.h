#ifndef TEA_SCRIPTING_SLOT_H
#define TEA_SCRIPTING_SLOT_H

struct WrenVM;

namespace tea {

class Slot {
public:
    Slot(WrenVM* wren_vm, int index);

    [[nodiscard]] bool is_bool() const;
    [[nodiscard]] bool is_double() const;
    [[nodiscard]] bool is_foreign() const;
    [[nodiscard]] bool is_list() const;
    [[nodiscard]] bool is_map() const;
    [[nodiscard]] bool is_null() const;
    [[nodiscard]] bool is_string() const;
    [[nodiscard]] bool is_unknown() const;
protected:
    WrenVM* wren_vm;
    const int index;
};

}

#endif // TEA_SCRIPTING_SLOT_H