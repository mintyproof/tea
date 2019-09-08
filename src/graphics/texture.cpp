#include "texture.h"

#include <glad/glad.h>

std::shared_ptr<Tea::Texture> Tea::Texture::create(const Image& image) {
    std::shared_ptr<Texture> tex(new Texture());

    glGenTextures(1, &tex->tex);
    glBindTexture(GL_TEXTURE_2D, tex->tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.get_width(), image.get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.get_data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    tex->width = image.get_width();
    tex->height = image.get_height();
    return tex;
}

Tea::Texture::~Texture() { glDeleteTextures(1, &this->tex); }

uint32_t Tea::Texture::get_width() { return this->width; }
uint32_t Tea::Texture::get_height() { return this->height; }
GLuint Tea::Texture::get_gl_texture() { return this->tex; }
