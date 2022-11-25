#ifndef TEA_SCRIPTING_SCRIPTING_H
#define TEA_SCRIPTING_SCRIPTING_H

struct WrenVM;
struct WrenHandle;

namespace tea {

class Slot;

class Scripting {
public:
    Scripting();
    ~Scripting();

    Slot slot(int slot_index);

    void test();
private:
    WrenVM* wren_vm;
};

}

#endif // TEA_SCRIPTING_SCRIPTING_H