#include "input.h"

#include <iostream>

#include "../engine.h"
#include "../module.h"

namespace Tea {
    Input::Input(Engine& engine): Module(engine) {
        this->engine.get_platform().set_key_callback([&](int keycode, Platform::KeyState state) {
            // TODO: make sure the `this` ptr here can't get use-after-free'd
            // it shouldn't because as a mostly-singleton this class only gets dealloc'd when we finish everything off
            if (keycode < 0 || keycode >= static_cast<int>(this->keys_down.size())) return;

            std::cout << "key update: " << keycode << " " << static_cast<int>(state) << std::endl;
            this->keys_down[keycode] = state == Platform::KeyState::Pressed;
        });
    }

    void Input::bind(Tea::ScriptingBinder&) {}

    bool Input::is_key_down(Keycode keycode) const noexcept {
        if (keycode >= this->keys_down.size()) return false;
        return this->keys_down[keycode];
    }

    bool Input::is_key_up(Input::Keycode keycode) const noexcept { return !this->is_key_down(keycode); }

    void Input::pre_update() {
        // todo: flip buffer for key_pressed/released
    }

    void Input::post_update() {}
}
