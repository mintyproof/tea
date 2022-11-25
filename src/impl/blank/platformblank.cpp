#include "impl/blank/platformblank.h"

#include <algorithm>

const int PLATFORM_BLANK_MAX_WIDTH = 1920;
const int PLATFORM_BLANK_MAX_HEIGHT = 1080;

namespace tea {

PlatformBlank::PlatformBlank() {
    window_width = 1920;
    window_height = 1080;
    window_title = "Tea";
}

PlatformBlank::~PlatformBlank() = default;

const char* PlatformBlank::get_name() const {
    return "Blank";
}

uint64_t PlatformBlank::runtime_milliseconds() const {
    return 0;
}

double PlatformBlank::runtime_seconds() const {
    return 0.0;
}

void PlatformBlank::poll_events() {
    // 👻
}

bool PlatformBlank::should_quit() const {
    return false;
}

int PlatformBlank::window_get_width() const {
    return window_width;
}

int PlatformBlank::window_get_height() const {
    return window_height;
}

std::string_view PlatformBlank::window_get_title() const {
    return window_title;
}

void PlatformBlank::window_set_size(int width, int height) {
    window_width = std::clamp(width, 1, PLATFORM_BLANK_MAX_WIDTH);
    window_height = std::clamp(height, 1, PLATFORM_BLANK_MAX_HEIGHT);
}

void PlatformBlank::window_set_title(const std::string& title) {
    window_title = title;
}

}