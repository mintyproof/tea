#include "renderer.h"

#include <iostream>

#include <glad/glad.h>
#include <wren.hpp>

#include "../assets/assets.h"
#include "../engine.h"

#define MAX_VERTICES 1024 * 32

static auto vertex_shader_source = R"glsl(#version 300 es
    precision mediump float;

    in vec2 v_position;
    in vec2 v_uv;
    in vec4 v_color;

    out vec2 f_uv;
    out vec4 f_color;

    uniform vec2 u_screen_size;

    void main() {
        f_uv = v_uv;
        f_color = v_color;

        vec2 half_size = u_screen_size / 2.0;
        gl_Position = vec4((v_position - half_size) / half_size, 0.0, 1.0);
    }
    )glsl";
static auto fragment_shader_source = R"glsl(#version 300 es
    precision mediump float;

    in vec2 f_uv;
    in vec4 f_color;

    out vec4 out_color;

    uniform sampler2D u_texture;

    void main() {
        out_color = texture(u_texture, f_uv) * f_color;
    }
)glsl";

namespace Tea {
    Renderer::Renderer(Engine& engine): Module(engine) { this->init(); }

    Renderer::~Renderer() {
        glDeleteBuffers(1, &this->vbo);
    }

    void Renderer::init() {
        std::cout << "Initializing render backend:" << std::endl;
        std::cout << " - GL " << glGetString(GL_VERSION) << std::endl;
        std::cout << " - Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << " - Renderer: " << glGetString(GL_RENDERER) << std::endl;

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        this->default_shader = Shader::compile(vertex_shader_source, fragment_shader_source);
        glUseProgram(this->default_shader->program);

        GLint posAttrib = glGetAttribLocation(this->default_shader->program, "v_position");
        GLint uvAttrib = glGetAttribLocation(this->default_shader->program, "v_uv");
        GLint colorAttrib = glGetAttribLocation(this->default_shader->program, "v_color");

        glVertexAttribPointer(
            posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, x)));

        glVertexAttribPointer(
            uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, u)));

        glVertexAttribPointer(colorAttrib,
                              4,
                              GL_UNSIGNED_BYTE,
                              GL_TRUE,
                              sizeof(Vertex),
                              reinterpret_cast<const void*>(offsetof(Vertex, abgr)));

        glEnableVertexAttribArray(posAttrib);
        glEnableVertexAttribArray(uvAttrib);
        glEnableVertexAttribArray(colorAttrib);

        this->screen_size_uniform = glGetUniformLocation(this->default_shader->program, "u_screen_size");

        Image pixel_image(1, 1, Color::white());
        this->pixel_texture = Texture::create(pixel_image);
        this->current_texture = this->pixel_texture;
    }

    void Renderer::clear(Color color) {
        glClearColor(color.r_float(), color.g_float(), color.b_float(), color.a_float());
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::push_vertices(const std::vector<Vertex>& vtcs) {
        if (this->vertices.size() + vtcs.size() >= MAX_VERTICES) flush();

        for (auto vertex : vtcs) this->vertices.push_back(vertex);
    }

    void Renderer::flush() {
        auto& platform = this->engine.get_platform();
        glUniform2f(this->screen_size_uniform,
                    static_cast<GLfloat>(platform.get_window_width()),
                    static_cast<GLfloat>(platform.get_window_height()));
        // TODO: This should probably be handled somewhere else?
        glViewport(0,
                   0,
                   static_cast<GLsizei>(platform.get_window_width()),
                   static_cast<GLsizei>(platform.get_window_height()));

        glBindTexture(GL_TEXTURE_2D, this->current_texture->get_gl_texture());

        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STREAM_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        vertices.resize(0);
    }

    void Renderer::set_texture(std::shared_ptr<Texture>& tex) {
        if (this->current_texture->get_gl_texture() != tex->get_gl_texture() && !this->vertices.empty()) flush();
        this->current_texture = tex;
    }

    void Renderer::set_shader(std::shared_ptr<Shader> &shader) {
        if (this->current_shader->program != shader->program && !this->vertices.empty()) flush();
        this->current_shader = shader;
        glUseProgram(shader->program);

        // TODO: Rebind vertex attrib pointers and such where relevant
    }

    void Renderer::rect(float x, float y, float w, float h, Color color) {
        uint32_t abgr = color.abgr();
        this->push_vertices({{x, y, 0, 0, abgr},
                             {x + w, y, 1, 0, abgr},
                             {x, y + h, 0, 1, abgr},
                             {x, y + h, 0, 1, abgr},
                             {x + w, y, 1, 0, abgr},
                             {x + w, y + h, 1, 1, abgr}});
    }

    void Renderer::draw_texture(std::shared_ptr<Texture>& tex, float x, float y, float w, float h, Color color) {
        this->set_texture(tex);
        rect(x, y, w, h, color);
    }

    void Renderer::draw_rect(float x, float y, float w, float h, Color color) {
        this->set_texture(pixel_texture);
        rect(x, y, w, h, color);
    }

    void Renderer::pre_update() { this->clear(Color::white()); }

    void Renderer::post_update() { this->flush(); }
}