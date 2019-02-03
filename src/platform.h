#ifndef TEA_PLATFORM_H
#define TEA_PLATFORM_H

#include <functional>
#include <memory>

namespace Tea {
    class Platform {
    public:
        enum class KeyState { Pressed, Released };
        
        static std::unique_ptr<Platform> init();

        virtual ~Platform() noexcept = default;

        virtual uint32_t get_window_width() const noexcept  = 0;
        virtual uint32_t get_window_height() const noexcept = 0;
        virtual void resize_window(uint32_t width, uint32_t height) = 0;

        virtual void set_key_callback(std::function<void(int, KeyState)> key_callback) noexcept = 0;

        // TODO: should this be an uint64_t? Variable or predefined precision?
        virtual double get_timer() const noexcept = 0;

        virtual void main_loop(std::function<void(double)> update_function) = 0;
    };
}

#endif