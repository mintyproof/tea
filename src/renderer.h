#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

namespace Tea {
    class Engine;
    class ScriptingBinder;

    struct Vertex {
        float x;
        float y;
        float u;
        float v;

        // Array and not uint32_t for endianness reasons
        // uint32_t would reverse the order when giving a literal
        uint8_t rgba[4];
    };

    class Renderer {
    public:
        Renderer(Engine& engine);
        ~Renderer();

        void init();

        static void bind(Tea::ScriptingBinder& binder);

        void begin();
        void push_vertex(Vertex vtx);
        void flush();

        void rect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    private:
        Engine& engine;

        GLuint vbo;
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;
        GLint  screen_size_uniform;

        std::vector<Vertex> vertices;
    };
}