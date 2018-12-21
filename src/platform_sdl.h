#ifndef TEA_PLATFORM_SDL_H
#define TEA_PLATFORM_SDL_H

#include <functional>
#include <memory>

#include <SDL.h>

#include "platform.h"

namespace Tea {
    class PlatformSDL;

    class PlatformSDLGraphics: public PlatformGraphics {
        friend PlatformSDL;

    public:
        explicit PlatformSDLGraphics(PlatformSDL& platform);
        ~PlatformSDLGraphics() noexcept override;

        uint32_t get_width() const noexcept override;
        uint32_t get_height() const noexcept override;

        void resize(uint32_t width, uint32_t height) override;

    private:
        PlatformSDL&  platform;
        SDL_GLContext gl;
    };

    class PlatformSDLInput: public PlatformInput {
        friend PlatformSDL;

    public:
        explicit PlatformSDLInput(PlatformSDL& platform);
        ~PlatformSDLInput() noexcept override;

        void set_key_callback(std::function<void(int, KeyState)> cb) noexcept override;

    private:
        std::function<void(int, KeyState)> key_callback;
        Platform&                          platform;
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