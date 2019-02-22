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
            this->keys_down[keycode] = state == Platform::KeyState::Pressed;
        });
    }

    void Input::bind(Scripting& s) {
        s.bind("static tea/input::Keyboard::isDown(_)", [](Scripting& s) {
            auto input   = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_down(keycode));
        });

        s.bind("static tea/input::Keyboard::isUp(_)", [](Scripting& s) {
            auto input   = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_up(keycode));
        });

        s.bind("static tea/input::Keyboard::isPressed(_)", [](Scripting& s) {
            auto input   = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_pressed(keycode));
        });

        s.bind("static tea/input::Keyboard::isReleased(_)", [](Scripting& s) {
            auto input   = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_released(keycode));
        });
    }

    bool Input::is_key_down(Keycode keycode) const noexcept {
        if (keycode >= this->keys_down.size()) return false;
        return this->keys_down[keycode];
    }

    bool Input::is_key_up(Input::Keycode keycode) const noexcept { return !this->is_key_down(keycode); }

    bool Input::is_key_pressed(Input::Keycode keycode) const noexcept {
        if (keycode >= this->keys_down.size()) return false;
        return this->keys_down[keycode] && !this->last_keys_down[keycode];
    }

    bool Input::is_key_released(Input::Keycode keycode) const noexcept {
        if (keycode >= this->keys_down.size()) return false;
        return !this->keys_down[keycode] && this->last_keys_down[keycode];
    } 

    void Input::pre_update() {
    }

    void Input::post_update() {
        this->last_keys_down = this->keys_down;
    }
}
