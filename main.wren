import "tea/graphics" for Graphics, Texture

class Main {
    construct init() {
        _tex = Texture.load("hello.png")
    }

    update(delta) {
        Graphics.setTexture(_tex)
        Graphics.rect(10, 10, 50, 50, 0xffffffff)
    }
}