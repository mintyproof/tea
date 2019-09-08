#include "shader.h"

#include <fmt/core.h>
#include <glad/glad.h>

static bool get_shader_compile_error(GLuint shader, std::string& error) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status) return false;

    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

    error.resize(length);
    glGetShaderInfoLog(shader, length, nullptr, &error.front());
    return true;
}

std::shared_ptr<Tea::Shader> Tea::Shader::compile(const std::string &vertex_source, const std::string &fragment_source) {
    return std::shared_ptr<Shader>(new Shader(vertex_source, fragment_source));
}

Tea::Shader::Shader(const std::string &vertex_source, const std::string &fragment_source) {
    this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    this->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Must be an lvalue...
    // Well, technically, glShaderSource takes an array of C strings
    // but since we only have one element we can just give it a pointer to a C string (ie. a char**)
    auto vertex_source_cstr = vertex_source.c_str();
    auto fragment_source_cstr = fragment_source.c_str();

    glShaderSource(this->vertex_shader, 1, &vertex_source_cstr, nullptr);
    glShaderSource(this->fragment_shader, 1, &fragment_source_cstr, nullptr);

    glCompileShader(this->vertex_shader);
    glCompileShader(this->fragment_shader);

    std::string error;
    if (get_shader_compile_error(this->vertex_shader, error)) {
        throw std::runtime_error(fmt::format("Error compiling vertex shader: {}", error));
    }

    if (get_shader_compile_error(this->fragment_shader, error)) {
        throw std::runtime_error(fmt::format("Error compiling fragment shader: {}", error));
    }

    this->program = glCreateProgram();
    glAttachShader(this->program, this->vertex_shader);
    glAttachShader(this->program, this->fragment_shader);
    glLinkProgram(this->program);

    // TODO: here, we essentially want to run the glVertexAttribPointer commands
    // assuming (and ensuring) the shader has v_position, v_uv and v_color varyings defined
    // as well as an u_screen_size uniform (to be replaced by a Matrix4 some day...)
    // Then, have a function or something to set up the proper buffer parameters keeping the same vertex layout
    // we currently do in the renderer. Dunno where this code should live but something like that, yeah.
}

Tea::Shader::~Shader() {
    glDetachShader(this->program, this->vertex_shader);
    glDetachShader(this->program, this->fragment_shader);
    glDeleteProgram(this->program);
    glDeleteShader(this->vertex_shader);
    glDeleteShader(this->fragment_shader);
}