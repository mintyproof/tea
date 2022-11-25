#include "core/platformcreator.h"

//#include "impl/blank/platformblank.h"
//#include "impl/blank/rendererblank.h"
#include "impl/platformsdl2.h"
#include "impl/renderergl33.h"

namespace tea {

std::tuple<std::shared_ptr<Platform>, std::shared_ptr<Renderer>> get_platform() {
    std::shared_ptr<PlatformSDL2> platform_sdl2 = std::make_shared<PlatformSDL2>();
    std::shared_ptr<Renderer> renderer = platform_sdl2->make_renderer_gl33();

    return std::make_tuple(std::move(platform_sdl2), std::move(renderer));
}

}