#ifndef TEA_RENDERER_H
#define TEA_RENDERER_H

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>
#include "../module.h"

namespace Tea {
    class Asset;
    class Engine;
    struct Vertex {
        float x;
        float y;

        float u;
        float v;

        float r;
        float g;
        float b;
        float a;
    };

    class Texture {
    public:
        static std::shared_ptr<Texture> load(const std::vector<uint8_t>& data);
        static std::shared_ptr<Texture> create(const std::vector<uint8_t>& data, uint32_t width, uint32_t height);
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

    class Color {
    public:
        static std::shared_ptr<Color> fromRGB(float r, float g, float b);
        static std::shared_ptr<Color> fromRGBA(float r, float g, float b, float a);

        Color(const Color&) = delete;
        Color& operator=(const Color&) = delete;

        float r;
        float g;
        float b;
        float a;
    private:
        Color(float r, float g, float b, float a);
    };

    class Renderer: public Module {
    public:
        explicit Renderer(Engine& engine);
        ~Renderer() override;

        void init();

        void bind(Tea::Scripting& s) override;
        void pre_update() override;
        void post_update() override;
        
        void clear(std::shared_ptr<Color>& color);
        void push_vertex(Vertex vtx);
        void flush();

        void set_texture(std::shared_ptr<Texture>& tex);

        void rect(float x, float y, float w, float h, std::shared_ptr<Color>& color);
        void draw_texture(std::shared_ptr<Texture>& tex, float x, float y, float w, float h, std::shared_ptr<Color>& color);
        void draw_rect(float x, float y, float w, float h, std::shared_ptr<Color>& color);
    private:
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

#endif