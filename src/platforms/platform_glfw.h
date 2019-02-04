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
        std::string get_window_title() const noexcept override;
        void set_window_title(std::string new_title) noexcept override;

        void set_key_callback(std::function<void(int, KeyState)> new_callback) noexcept override;

        double get_timer() const noexcept override;

        void main_loop(std::function<void(double)> update_function) override;
    private:
        static void glfw_error_callback(int error, const char* description);
        static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        std::function<void(int, KeyState)> key_callback;

        GLFWwindow* window;

        // GLFW doesn't keep the title internally so we save it here for the get_window_title call
        std::string window_title;
    };
}

#endif