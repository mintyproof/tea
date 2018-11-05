System.print("Hello world!")

class Main {
    construct init() {
        System.print("Initializing...")
        _calls = 0
    }

    update(delta) {
        _calls = _calls + 1
        System.print("Updating (%(_calls) update calls)")
    }
}