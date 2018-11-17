#include "renderer.h"

#include <iostream>

#include <glad/glad.h>

#include "engine.h"

#define MAX_VERTICES 1024 * 32

static auto vertex_shader_source   = R"glsl(
    #version 300 es
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
static auto fragment_shader_source = R"glsl(
    #version 300 es
    precision mediump float;

    in vec2 f_uv;
    in vec4 f_color;

    out vec4 out_color;

    void main() {
        out_color = f_color;
    }
)glsl";

namespace Tea {
    Renderer::Renderer(Engine& engine): engine(engine) {}

    Renderer::~Renderer() {
        glDeleteBuffers(1, &this->vbo);
        glDetachShader(this->program, this->vertex_shader);
        glDetachShader(this->program, this->fragment_shader);
        glDeleteProgram(this->program);
        glDeleteShader(this->vertex_shader);
        glDeleteShader(this->fragment_shader);
    }

    bool get_shader_compile_error(GLuint shader, std::string& error) {
        GLint status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (status) return false;

        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        error.resize(length);
        glGetShaderInfoLog(shader, length, nullptr, &error.front());
        return true;
    }

    void Renderer::init() {
        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        this->vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
        this->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(this->vertex_shader, 1, &vertex_shader_source, nullptr);
        glShaderSource(this->fragment_shader, 1, &fragment_shader_source, nullptr);

        glCompileShader(this->vertex_shader);
        glCompileShader(this->fragment_shader);

        std::string error;
        if (get_shader_compile_error(this->vertex_shader, error)) {
            std::cerr << "Error compiling vertex shader: " << error << std::endl;
            exit(1);
        }

        if (get_shader_compile_error(this->fragment_shader, error)) {
            std::cerr << "Error compiling fragment shader: " << error << std::endl;
            exit(1);
        }

        this->program = glCreateProgram();
        glAttachShader(this->program, this->vertex_shader);
        glAttachShader(this->program, this->fragment_shader);
        glLinkProgram(this->program);
        glUseProgram(this->program);

        GLint posAttrib   = glGetAttribLocation(this->program, "v_position");
        GLint colorAttrib = glGetAttribLocation(this->program, "v_color");
        glVertexAttribPointer(
            posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, x)));
        glVertexAttribPointer(colorAttrib,
                              4,
                              GL_UNSIGNED_BYTE,
                              GL_TRUE,
                              sizeof(Vertex),
                              reinterpret_cast<const void*>(offsetof(Vertex, rgba)));

        glEnableVertexAttribArray(posAttrib);
        glEnableVertexAttribArray(colorAttrib);

        this->screen_size_uniform = glGetUniformLocation(this->program, "u_screen_size");
    }

    void Renderer::bind(Tea::ScriptingBinder& binder) {}

    void Renderer::begin() {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::push_vertex(Vertex vtx) {
        if (this->vertices.size() >= MAX_VERTICES) flush();
        this->vertices.push_back(vtx);
    }

    void Renderer::flush() {
        auto graphics = this->engine.get_platform().get_graphics();
        glUniform2f(this->screen_size_uniform, graphics.get_width(), graphics.get_height());

        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STREAM_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        GLint error;
        if ((error = glGetError()) != GL_NO_ERROR) std::cerr << "GL error: " << error << std::endl;

        vertices.resize(0);
    }

    void Renderer::rect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->push_vertex({x, y, 0, 0, {r, g, b, a}});
        this->push_vertex({x + w, y, 0, 0, {r, g, b, a}});
        this->push_vertex({x, y + h, 0, 0, {r, g, b, a}});
        this->push_vertex({x, y + h, 0, 0, {r, g, b, a}});
        this->push_vertex({x + w, y, 0, 0, {r, g, b, a}});
        this->push_vertex({x + w, y + h, 0, 0, {r, g, b, a}});
    }
}