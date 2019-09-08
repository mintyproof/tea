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
#include "../graphics/shader.h"

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
        void set_shader(std::shared_ptr<Shader>& shader);

        void rect(float x, float y, float w, float h, Color color);
        void draw_texture(std::shared_ptr<Texture>& tex, float x, float y, float w, float h, Color color);
        void draw_rect(float x, float y, float w, float h, Color color);

    private:
        GLuint vbo;

        GLint screen_size_uniform;

        // TODO: should these be shared_ptrs? Or should we have a unique_ptr of pixel_texture and default_shader
        std::shared_ptr<Texture> current_texture;
        std::shared_ptr<Texture> pixel_texture;

        std::shared_ptr<Shader> current_shader;
        std::shared_ptr<Shader> default_shader;

        std::vector<Vertex> vertices;
    };
}

#endif