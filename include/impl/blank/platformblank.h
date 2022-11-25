#ifndef TEA_IMPL_BLANK_PLATFORMBLANK_H
#define TEA_IMPL_BLANK_PLATFORMBLANK_H

#include "core/platform.h"

namespace tea {

// this is a blank platform, which does not perform any OS-specific actions- it simply does the bare minimum to
// pretend to be a platform.
// as such, this platform will not open a window or run a game in a way the end user can interact with.
//
// various potential uses of this:
// - porting to a new platform and attempting to get Tea compiling before implementing platform-specific behaviour
// - placing Tea in a "headless" mode, for running projects that have no need for graphical output
// - implementing unit tests and using the blank platform as part of functionality tests
class PlatformBlank : public Platform {
public:
    PlatformBlank();
    ~PlatformBlank() override;

    [[nodiscard]] const char* get_name() const override;

    [[nodiscard]] uint64_t runtime_milliseconds() const override;
    [[nodiscard]] double runtime_seconds() const override;

    void poll_events() override;
    [[nodiscard]] bool should_quit() const override;

    [[nodiscard]] int window_get_width() const override;
    [[nodiscard]] int window_get_height() const override;
    [[nodiscard]] std::string_view window_get_title() const override;
    void window_set_size(int width, int height) override;

    void window_set_title(const std::string& title) override;
private:
    int window_width, window_height;
    std::string window_title;
};

}

#endif