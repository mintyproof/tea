#ifndef TEA_SHADER_H
#define TEA_SHADER_H

#include <memory>
#include <string>

#include "../vec.h"

namespace Tea {
    class Shader {
        friend class Renderer; // todo: remove once todos in shader.cpp are resolved
    public:
        static std::shared_ptr<Shader> compile(const std::string& vertex_source, const std::string& fragment_source);
        ~Shader();

    private:
        Shader(const std::string& vertex_source, const std::string& fragment_source);
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        unsigned int program;
    };
}

#endif