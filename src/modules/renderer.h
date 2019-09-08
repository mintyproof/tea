#ifndef TEA_RENDERER_H
#define TEA_RENDERER_H

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>
#include "../graphics/color.h"
#include "../module.h"
#include "../assets/image/image.h"
#include "../graphics/texture.h"

namespace Tea {
    class Engine;
    struct Vertex {
        float x;
        float y;

        float u;
        float v;

        // OpenGL reads this backwards, so storing this in agbr format (little endian)
        // means it reads the vec4 [r, g, b, a]
        uint32_t abgr;
    };

    class Renderer: public Module {
    public:
        explicit Renderer(Engine& engine);
        ~Renderer() override;

        void init();

        void pre_update() override;
        void post_update() override;

        void clear(Color color);
        void push_vertices(const std::vector<Vertex>& vtcs);
        void flush();

        void set_texture(std::shared_ptr<Texture>& tex);

        void rect(float x, float y, float w, float h, Color color);
        void draw_texture(std::shared_ptr<Texture>& tex, float x, float y, float w, float h, Color color);
        void draw_rect(float x, float y, float w, float h, Color color);

    private:
        GLuint vbo;

        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint program;
        GLint screen_size_uniform;

        std::shared_ptr<Texture> current_texture;
        std::shared_ptr<Texture> pixel_texture;

        std::vector<Vertex> vertices;
    };
}

#endif