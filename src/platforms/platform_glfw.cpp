#include "platform_glfw.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>
#include <memory>

namespace Tea {
    void GLFWPlatform::glfw_error_callback(int error, const char* description) {
        std::cerr << "GLFW error " << error << ": " << description << std::endl;
    }

    void GLFWPlatform::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto platform = static_cast<GLFWPlatform*>(glfwGetWindowUserPointer(window));

        // TODO: use scancodes or keycodes here?
        // TODO: make a consistent scancode mapping, or bite the bullet and use strings (lmao)
        if (action == GLFW_PRESS) {
            platform->key_callback(scancode, KeyState::Pressed);   
        } else if (action == GLFW_RELEASE) {
            platform->key_callback(scancode, KeyState::Released);
        }
    }

    std::unique_ptr<Platform> Platform::init() {
        return std::unique_ptr<Platform>(new GLFWPlatform());
    }

    GLFWPlatform::GLFWPlatform() {
        this->window_title = "Hello World";

        std::cout << "Initializing GLFW backend: " << glfwGetVersionString() << std::endl;

        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) {
            std::terminate();
        }

        this->window = glfwCreateWindow(640, 480, this->window_title.c_str(), nullptr, nullptr);
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

    GLFWPlatform::~GLFWPlatform() noexcept {
        glfwTerminate();
    }

    uint32_t GLFWPlatform::get_window_width() const noexcept {
        int width, height;
        glfwGetWindowSize(this->window, &width, &height);
        return static_cast<uint32_t>(width);
    }

    uint32_t GLFWPlatform::get_window_height() const noexcept {
        int width, height;
        glfwGetWindowSize(this->window, &width, &height);
        return static_cast<uint32_t>(height);
    }

    void GLFWPlatform::resize_window(uint32_t width, uint32_t height) {
        glfwSetWindowSize(this->window, width, height);
    }

    std::string GLFWPlatform::get_window_title() const noexcept {
        return this->window_title;
    }

    void GLFWPlatform::set_window_title(std::string new_title) noexcept {
        glfwSetWindowTitle(this->window, new_title.c_str());
        this->window_title = new_title;
    }

    void GLFWPlatform::set_key_callback(std::function<void(int, KeyState)> new_callback) noexcept {
        this->key_callback = new_callback;
    }

    double GLFWPlatform::get_timer() const noexcept {
        return glfwGetTime();
    }

    void GLFWPlatform::main_loop(std::function<void(double)> update_function) {
        glfwSwapInterval(1);

        double timer = glfwGetTime();
        while (!glfwWindowShouldClose(this->window)) {
            double new_time = glfwGetTime();
            double delta = new_time - timer;
            update_function(delta);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
}