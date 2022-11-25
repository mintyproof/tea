class Tea {
    foreign static test(string)
}

class Main {
    construct on_start() {
        Tea.test("world")
    }

    on_quit() {
        Tea.test("c++")
    }

    on_update(dt) {
    }

    on_draw(dt) {
    }
}