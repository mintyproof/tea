#ifndef TEA_CORE_PLATFORM_H
#define TEA_CORE_PLATFORM_H

#include <cstdint>
#include <string>
#include "utils/nocopy.h"

namespace tea {

enum class WindowFlags {
    Resizable        = 1 << 0,
    Borderless       = 1 << 1,
    StartsMaximized  = 1 << 2,
    StartsFullscreen = 1 << 3
};

class Platform : public NoCopy {
public:
    virtual ~Platform() = default;

    // returns a name identifying the platform.
    [[nodiscard]] virtual const char* get_name() const = 0;

    // returns the amount of time, in milliseconds, since the platform started.
    // not guaranteed to start at zero.
    [[nodiscard]] virtual uint64_t runtime_milliseconds() const = 0;

    // returns the amount of time, in seconds, since the platform started.
    // not guaranteed to start at zero.
    [[nodiscard]] virtual double runtime_seconds() const = 0;

    virtual void poll_events() = 0;

    // returns whether the platform wants to shut down the engine and exit.
    // this becomes true in various circumstances- most commonly, the user clicking the close button on Tea's window.
    [[nodiscard]] virtual bool should_quit() const = 0;

    // returns the width of the window on-screen.
    // for high-DPI displays- for example, most macOS computers- this may not reflect the actual size of the drawable
    // portion of the window; for determining how wide the drawable area is, see Renderer's get_drawable_width()
    [[nodiscard]] virtual int window_get_width() const = 0;

    // returns the height of the window on-screen.
    // for high-DPI displays- for example, most macOS computers- this may not reflect the actual size of the drawable
    // portion of the window; for determining how tall the drawable area is, see Renderer's get_drawable_height()
    [[nodiscard]] virtual int window_get_height() const = 0;

    // returns the title of the window.
    [[nodiscard]] virtual std::string_view window_get_title() const = 0;

    // resizes the window.
    virtual void window_set_size(int width, int height) = 0;

    // alters the title of the window.
    virtual void window_set_title(const std::string& title) = 0;
};

}

#endif
