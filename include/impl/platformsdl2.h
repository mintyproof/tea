#ifndef TEA_IMPL_PLATFORMSDL2_H
#define TEA_IMPL_PLATFORMSDL2_H

#include <cstdint>
#include <string>
#include "core/platform.h"

union SDL_Event;
struct SDL_Window;

namespace tea {

class RendererGL33;

class PlatformSDL2 : public Platform {
public:
    PlatformSDL2();
    ~PlatformSDL2();

    [[nodiscard]] uint64_t runtime_milliseconds() const override;
    [[nodiscard]] double runtime_seconds() const override;

    void poll_events() override;
    [[nodiscard]] bool should_quit() const override;

    [[nodiscard]] int window_get_width() const override;
    [[nodiscard]] int window_get_height() const override;
    [[nodiscard]] std::string_view window_get_title() const override;
    void window_set_size(int width, int height) override;
    void window_set_title(const std::string& title) override;

    RendererGL33 make_renderer_gl33();
private:
    SDL_Window* window;
    std::string window_title;

    // the value of SDL_GetTicks64() when this instance of PlatformSDL2 was created,
    // used to make runtime_milliseconds() start at zero.
    uint64_t ticks_at_init;

    // the value of SDL_GetPerformanceCounter() when this instance of PlatformSDL2 was created,
    // used to make runtime_seconds() start at zero.
    uint64_t performance_counter_at_init;

    // used to count how many PlatformSDL2 instances exist for knowing when to initialize & exit SDL2 proper
    static unsigned int platform_count;

    // is it time to call it quits?
    bool quit;
};

}

#endif