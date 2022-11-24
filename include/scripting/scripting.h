#ifndef TEA_SCRIPTING_H
#define TEA_SCRIPTING_H

struct WrenVM;
struct WrenHandle;

namespace tea {

class Scripting {
public:
    Scripting();
    ~Scripting();

    void test();
private:
    WrenVM* wren_vm;
};

}

#endif // TEA_SCRIPTING_H