#ifndef TEA_MODULE_H
#define TEA_MODULE_H

#include "utils.h"

namespace Tea {
    class Engine;

    class Module {
    public:
        explicit Module(Engine& engine): engine(engine) {}

        virtual ~Module() {}

        virtual void bind(Tea::ScriptingBinder&) {}
        virtual void pre_update() {}
        virtual void post_update() {}
    protected:
        Engine& engine;
    };
}

#endif