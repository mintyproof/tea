import "tea/graphics" for Graphics, Texture
import "tea/input" for Keys

class Main {
    construct init() {
        _tex1 = Texture.load("hello.png")
        _tex2 = Texture.load("test.png")
    }

    update(delta) {
        Graphics.drawRect(400, 350, 75, 15, 0xff0000ff)
        Graphics.drawTexture(_tex1, 200, 50)
        Graphics.drawTexture(_tex2, 200, 150, 300, 16)
        Graphics.drawRect(500, 350, 75, 15, 0xffffffff)
    }
}