#include "platform_glfw.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>
#include <memory>

void error_callback(int error, const char* description) {
    std::cerr << "GLFW error " << error << ": " << description << std::endl;
}

std::unique_ptr<Tea::Platform> Tea::Platform::init() {
    return std::unique_ptr<Tea::Platform>(new GLFWPlatform());
}

Tea::GLFWPlatform::GLFWPlatform() {
    std::cout << "Initializing GLFW backend: " << glfwGetVersionString() << std::endl;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::terminate();
    }

    this->window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (this->window == nullptr) {
        std::terminate();
    }

    glfwSetWindowUserPointer(this->window, static_cast<void*>(this));

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwMakeContextCurrent(window);
    gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress);
}

Tea::GLFWPlatform::~GLFWPlatform() noexcept {
    glfwTerminate();
}

uint32_t Tea::GLFWPlatform::get_window_width() const noexcept {
    return 0;
}

uint32_t Tea::GLFWPlatform::get_window_height() const noexcept {
    return 0;
}

void Tea::GLFWPlatform::resize_window(uint32_t width, uint32_t height) {
}

void Tea::GLFWPlatform::set_key_callback(std::function<void(int, KeyState)> new_calback) noexcept {
    this->key_callback = key_callback;
}

void Tea::GLFWPlatform::main_loop(std::function<void(double)> update_function) {
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}