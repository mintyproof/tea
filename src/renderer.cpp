#include "renderer.h"

#include <glad/glad.h>

#define MAX_VERTICES 1024 * 32

namespace Tea {
    void Renderer::bind(Tea::ScriptingBinder& binder) {}

    void Renderer::push_vertex(Vertex vtx) {
        if (this->vertices.size() >= MAX_VERTICES) flush();
        this->vertices.push_back(vtx);
    }

    void Renderer::flush() {}
}