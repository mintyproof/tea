#ifndef TEA_MODULE_H
#define TEA_MODULE_H

namespace Tea {
    class Engine;

    class Module {
    public:
        explicit Module(Engine& engine): engine(engine) {}
        Module(const Module&) = delete;
        Module(Module&&) = delete;

        virtual ~Module() {}

        virtual void pre_update() {}
        virtual void post_update() {}

    protected:
        Engine& engine;
    };
}

#endif