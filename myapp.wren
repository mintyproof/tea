import "tea/graphics" for Graphics

class Main {
    construct init() {
    }

    update(delta) {
        Graphics.rect(10, 10, 50, 50, 0x00ff00ff)
    }
}