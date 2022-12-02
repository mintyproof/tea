class Tea {
    foreign static clear_to_colour(r, g, b)
}

class Main {
    construct on_start() {
    }

    on_quit() {
    }

    on_update(dt) {
    }

    on_draw(dt) {
        Tea.clear_to_colour(0, 0, 0)
    }
}

class Prelude {
    static run(mainClass) {
        __mainClassInstance = mainClass.on_start()
        return __mainClassInstance
    }
}
var mainClassInstance = Main.on_start()