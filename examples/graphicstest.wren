import "tea/graphics" for Graphics, Texture, Color
import "tea/input" for Keys

class Main {
    construct init() {
        _red = Color.fromRGB(1.0, 0.0, 0.0)
        _green = Color.fromRGBA(0.0, 1.0, 0.0, 1.0)
        _blue = Color.fromRGBA(0.0, 0.0, 1.0, 1.0)

        _tex1 = Texture.load("hello.png")
        _tex2 = Texture.load("test.png")
    }

    update(delta) {
        Graphics.clear(Color.fromRGB(100 / 255, 149 / 255, 237 / 255))
        Graphics.drawRect(400, 350, 75, 15, _red)
        Graphics.drawTexture(_tex1, 200, 50)
        Graphics.drawTexture(_tex2, 200, 150, 300, 16, _green)
        Graphics.drawTexture(_tex2, 200, 250, 50, 50)
        Graphics.drawRect(500, 350, 75, 15, _blue)
    }
}