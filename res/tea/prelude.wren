class Prelude {
    static run(mainClass) {
        __mainClassInstance = mainClass.init()
    }

    static update(delta) {
        __mainClassInstance.update(delta)
    }
}