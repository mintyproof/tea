#ifndef TEA_GRAPHICS_H
#define TEA_GRAPHICS_H

#include <memory>

namespace tea {

class ColourRGB;
class Renderer;

class Graphics {
public:
    explicit Graphics(std::shared_ptr<Renderer> renderer);

    void clear_to_colour(ColourRGB colour);
protected:
    std::shared_ptr<Renderer> renderer;
};

}

#endif // TEA_GRAPHICS_H
