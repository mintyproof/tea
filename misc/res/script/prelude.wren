class Prelude {
    static run(mainClass) {
        __mainClassInstance = mainClass.on_start()
        return __mainClassInstance
    }
}