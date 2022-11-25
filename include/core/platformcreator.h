#ifndef TEA_PLATFORMCREATOR_H
#define TEA_PLATFORMCREATOR_H

// TODO: unsure if this feels like the right way to be going about this? feels a lil too baked-in..

#include <memory>
#include <tuple>

namespace tea {

class Platform;
class Renderer;

std::tuple<std::unique_ptr<Platform>, std::shared_ptr<Renderer>> get_platform();

}

#endif // TEA_PLATFORMCREATOR_H
