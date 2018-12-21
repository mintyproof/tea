#ifndef TEA_PLATFORM_H
#define TEA_PLATFORM_H

#include <functional>

namespace Tea {
    class PlatformGraphics {
    public:
        virtual ~PlatformGraphics() noexcept = default;

        virtual uint32_t get_width() const noexcept  = 0;
        virtual uint32_t get_height() const noexcept = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;
    };

    class PlatformInput {
    public:
        enum class KeyState { Pressed, Released };
        virtual ~PlatformInput() noexcept = default;

        virtual void set_key_callback(std::function<void(int, KeyState)> key_callback) noexcept = 0;
    };

    class Platform {
    public:
        static std::unique_ptr<Platform> init();

        virtual ~Platform() noexcept = default;

        virtual PlatformGraphics& get_graphics() noexcept = 0;
        virtual PlatformInput&    get_input() noexcept    = 0;

        virtual void main_loop(std::function<void(double)> update_function) = 0;
    };
}

#endif