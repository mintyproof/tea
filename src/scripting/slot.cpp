#include "scripting/slot.h"

#include <wren.hpp>

namespace tea {

Slot::Slot(WrenVM* wren_vm, int index): wren_vm(wren_vm), index(index) {}

bool Slot::is_bool() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_BOOL;
}

bool Slot::is_double() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_NUM;
}

bool Slot::is_foreign() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_FOREIGN;
}

bool Slot::is_list() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_LIST;
}

bool Slot::is_map() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_MAP;
}

bool Slot::is_null() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_NULL;
}

bool Slot::is_string() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_STRING;
}

bool Slot::is_unknown() const {
    return wrenGetSlotType(wren_vm, index) == WREN_TYPE_UNKNOWN;
}

}