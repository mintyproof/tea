#ifndef TEA_INPUT_H
#define TEA_INPUT_H

#include <array>

#include "../module.h"

namespace Tea {
    class Input: public Module {
    public:
        using Keycode = unsigned int;

        explicit Input(Engine& engine);

        void bind(Tea::Scripting& s) override;

        bool is_key_down(Keycode keycode) const noexcept;
        bool is_key_up(Keycode keycode) const noexcept;
        bool is_key_pressed(Keycode keycode) const noexcept;
        bool is_key_released(Keycode keycode) const noexcept;

        void pre_update() override;
        void post_update() override;

    private:
        std::array<bool, 500> keys_down;  // TODO: define a proper set of keycodes that are platform independent
        std::array<bool, 500> last_keys_down;
    };
}

#endif
