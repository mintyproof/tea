class Prelude {
    static run(mainClass) {
        __mainClassInstance = mainClass.init()
    }

    static onUpdate(deltaTime) {
        __mainClassInstance.onUpdate(deltaTime)
    }
}