#include <string>
#include <vector>

namespace Tea {
    class ScriptingBinder;

    struct Vertex {
        float    x;
        float    y;
        float    u;
        float    v;
        uint32_t rgba;
    };

    class Renderer {
    public:
        static void bind(Tea::ScriptingBinder& binder);

        void push_vertex(Vertex vtx);
        void flush();

    private:
        std::vector<Vertex> vertices;
    };
}