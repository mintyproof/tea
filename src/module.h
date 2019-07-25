#ifndef TEA_MODULE_H
#define TEA_MODULE_H

namespace Tea {
    class Engine;

    class Module {
    public:
        explicit Module(Engine& engine): engine(engine) {}

        virtual ~Module() {}

        virtual void pre_update() {}
        virtual void post_update() {}

    protected:
        Engine& engine;
    };
}

#endif