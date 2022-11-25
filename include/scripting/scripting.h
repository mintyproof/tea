#ifndef TEA_SCRIPTING_H
#define TEA_SCRIPTING_H

#include <iosfwd>

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