#include <functional>
#include <memory>

#include <SDL.h>

namespace Tea {
    class Platform;

    class PlatformGraphics {
    public:
        PlatformGraphics(Platform& platform);
        ~PlatformGraphics();

        uint32_t get_width();
        uint32_t get_height();

        void resize(uint32_t width, uint32_t height);

    private:
        Platform&     platform;
        SDL_GLContext gl;
    };

    class PlatformInput {
    public:
        PlatformInput(Platform& platform);
        ~PlatformInput();

        bool is_key_down(int keycode);
        bool is_key_up(int keycode);

        bool is_key_pressed(int keycode);
        bool is_key_released(int keycode);

    private:
        Platform& platform;
    };

    class Platform {
        friend PlatformGraphics;
        friend PlatformInput;

    public:
        Platform();
        ~Platform();

        PlatformGraphics& get_graphics();
        PlatformInput&    get_input();

        void main_loop(std::function<void(double)> update_function);

    private:
        std::unique_ptr<PlatformGraphics> graphics{nullptr};
        std::unique_ptr<PlatformInput>    input{nullptr};
        SDL_Window*                       window;
    };
}