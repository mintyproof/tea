import "tea/assets" for Assets
import "tea/graphics" for Graphics, Texture, Color
import "tea/input" for Keys, Keyboard

class Main {
    construct init() {
        _red = Color.rgb(0xFF0000)
        _green = Color.rgb(0x00FF00)
        _blue = Color.rgb(0x0000FF)

        _tex1 = Assets.texture("hello.png")
        _tex2 = Assets.texture("test.png")

        _x = 300
        _speed = 64
    }

    update(delta) {
        if (Keyboard.isDown(Keys.d)) {
            _x = _x + _speed * delta
        } else if (Keyboard.isDown(Keys.a)) {
            _x = _x - _speed * delta
        }

        Graphics.clear(Color.rgb(100, 149, 237))
        Graphics.drawRect(400, 350, 75, 15, _red)
        Graphics.drawTexture(_tex1, 200, 50)
        Graphics.drawTexture(_tex2, 200, 150, 300, 16, _green)
        Graphics.drawTexture(_tex2, 200, 250, 50, 50)
        Graphics.drawRect(500, 350, 75, 15, _blue)
        Graphics.drawTexture(_tex1, _x, 350)
    }
}