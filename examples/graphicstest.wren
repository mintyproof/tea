import "tea/graphics" for Graphics, Texture
import "tea/input" for Keys

class Main {
    construct init() {
        _tex = Texture.load("hello.png")
    }

    update(delta) {
        Graphics.setTexture(_tex)
        Graphics.drawRectangle(100, 100, 50, 50, 0xffffffff)
    }
}