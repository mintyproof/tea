/* weeeee are missing:
 *     drawTexture(texture, x, y, w, h, color, rot)
 *     drawSubtexture(texture, x, y, w, h, ix, iy, iw, ih)
 *     drawSubtexture(texture, x, y, w, h, ix, iy, iw, ih, color)
 *     drawSubtexture(texture, x, y, w, h, ix, iy, iw, ih, color, rot)
 *     drawRect(x, y, w, h, color, rot)
 *     drawCircle(x, y, radius, color)
 */

class Graphics {
    foreign static clear(color)
    foreign static drawTexture(tex, x, y)
    foreign static drawTexture(tex, x, y, w, h)
    foreign static drawTexture(tex, x, y, w, h, color)
    foreign static drawRect(x, y, w, h, color)
}

foreign class Texture {
    foreign static load(filename)

    foreign width
    foreign height
}

foreign class Color {
    foreign static rgba(r, g, b, a)
    foreign static rgba(rgba)

    foreign static rgb(r, g, b)
    foreign static rgb(rgb)

    // Parse as string
    foreign static hex(hex)

    foreign r
    foreign g
    foreign b
    foreign a
}