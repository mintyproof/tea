#ifndef TEA_PLATFORM_GLFW_H
#define TEA_PLATFORM_GLFW_H

#include "../platform.h"

struct GLFWwindow;

namespace Tea {
    class GLFWPlatform: public Platform {
    public:
        explicit GLFWPlatform();
        ~GLFWPlatform() noexcept override;

        uint32_t get_window_width() const noexcept override;
        uint32_t get_window_height() const noexcept override;
        void resize_window(uint32_t width, uint32_t height) override;

        void set_key_callback(std::function<void(int, KeyState)> new_callback) noexcept override;

        void main_loop(std::function<void(double)> update_function) override;
    private:
        std::function<void(int, KeyState)> key_callback;

        GLFWwindow* window;
    };
}

#endif