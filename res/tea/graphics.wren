/* weeeee are missing:
 *     clear(color)
 *     present()
 *     drawTexture(texture, x, y, w, h, color)
 *     drawTexture(texture, x, y, w, h, color, rot)
 *     drawSubtexture(texture, x, y, w, h, ix, iy, iw, ih)
 *     drawSubtexture(texture, x, y, w, h, ix, iy, iw, ih, color)
 *     drawSubtexture(texture, x, y, w, h, ix, iy, iw, ih, color, rot)
 *     drawRectangle(x, y, w, h, color)
 *     drawRectangle(x, y, w, h, color, rot)
 *     drawCircle(x, y, radius, color)
 */

class Graphics {
    foreign static drawTexture(tex, x, y)
    foreign static drawTexture(tex, x, y, w, h)
    foreign static drawRect(x, y, w, h, color)
}

foreign class Texture {
    foreign static load(filename)

    foreign width
    foreign height
}

foreign class Color {
    foreign static fromRGB(r, g, b)
    foreign static fromRGBA(r, g, b, a)

    foreign r
    foreign g
    foreign b
    foreign a
}