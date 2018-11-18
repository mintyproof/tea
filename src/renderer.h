#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>

namespace Tea {
    class Asset;
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

    class Texture {
    public:
        static std::shared_ptr<Texture> load(Asset& asset);
        static std::shared_ptr<Texture> create(std::vector<uint8_t>& data, uint32_t width, uint32_t height);
        ~Texture();

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        uint32_t get_width();
        uint32_t get_height();

        GLuint get_gl_texture();

    private:
        Texture() = default;

        GLuint   tex;
        uint32_t width;
        uint32_t height;
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

        void set_texture(std::shared_ptr<Texture>& tex);

        void rect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    private:
        Engine& engine;

        GLuint vbo;

        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;
        GLint  screen_size_uniform;

        std::shared_ptr<Texture> current_texture;
        std::shared_ptr<Texture> pixel_texture;

        std::vector<Vertex> vertices;
    };
}