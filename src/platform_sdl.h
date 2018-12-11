#ifndef TEA_PLATFORM_SDL_H
#define TEA_PLATFORM_SDL_H

#include <functional>
#include <memory>

#include <SDL.h>

#include "platform.h"

namespace Tea {
    class PlatformSDL;

    class PlatformSDLGraphics: public PlatformGraphics {
    public:
        PlatformSDLGraphics(PlatformSDL& platform);
        ~PlatformSDLGraphics() noexcept override;

        uint32_t get_width() const noexcept override;
        uint32_t get_height() const noexcept override;

        void resize(uint32_t width, uint32_t height);

    private:
        PlatformSDL&  platform;
        SDL_GLContext gl;
    };

    class PlatformSDLInput: public PlatformInput {
    public:
        PlatformSDLInput(PlatformSDL& platform);
        ~PlatformSDLInput() noexcept override;

        bool is_key_down(int keycode) const noexcept override;
        bool is_key_up(int keycode) const noexcept override;

        bool is_key_pressed(int keycode) const noexcept override;
        bool is_key_released(int keycode) const noexcept override;

    private:
        Platform& platform;
    };

    class PlatformSDL: public Platform {
        friend PlatformSDLGraphics;
        friend PlatformSDLInput;

    public:
        PlatformSDL();
        ~PlatformSDL() noexcept override;

        PlatformGraphics& get_graphics() noexcept override;
        PlatformInput&    get_input() noexcept override;

        void main_loop(std::function<void(double)> update_function) override;

    private:
        std::unique_ptr<PlatformSDLGraphics> graphics{nullptr};
        std::unique_ptr<PlatformSDLInput>    input{nullptr};
        SDL_Window*                          window;
    };
}

#endif