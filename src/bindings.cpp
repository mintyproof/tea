#include "bindings.h"

#include <memory>
#include "color.h"
#include "engine.h"
#include "modules/input.h"
#include "modules/renderer.h"
#include "scripting.h"

namespace Tea {
    void bind_graphics(Scripting& s) {
        s.bind("static tea/graphics::Graphics::clear(_)", [](Tea::Scripting& s) {
            Color color = s.slot(1).get_native_type<Color>();
            s.get_engine().get_module<Renderer>()->clear(color);
        });

        s.bind("static tea/graphics::Graphics::drawTexture(_,_,_)", [](Tea::Scripting& s) {
            std::shared_ptr<Texture> texture = s.slot(1).get_native_type<std::shared_ptr<Texture>>();
            s.get_engine().get_module<Renderer>()->draw_texture(texture,
                                                                static_cast<float>(s.slot(2).as_num()),
                                                                static_cast<float>(s.slot(3).as_num()),
                                                                static_cast<float>(texture->get_width()),
                                                                static_cast<float>(texture->get_height()),
                                                                Color::white());
        });

        s.bind("static tea/graphics::Graphics::drawTexture(_,_,_,_,_)", [](Tea::Scripting& s) {
            std::shared_ptr<Texture> texture = s.slot(1).get_native_type<std::shared_ptr<Texture>>();
            s.get_engine().get_module<Renderer>()->draw_texture(texture,
                                                                static_cast<float>(s.slot(2).as_num()),
                                                                static_cast<float>(s.slot(3).as_num()),
                                                                static_cast<float>(s.slot(4).as_num()),
                                                                static_cast<float>(s.slot(5).as_num()),
                                                                Color::white());
        });

        s.bind("static tea/graphics::Graphics::drawTexture(_,_,_,_,_,_)", [](Tea::Scripting& s) {
            std::shared_ptr<Texture> texture = s.slot(1).get_native_type<std::shared_ptr<Texture>>();
            Color color = s.slot(6).get_native_type<Color>();
            s.get_engine().get_module<Renderer>()->draw_texture(texture,
                                                                static_cast<float>(s.slot(2).as_num()),
                                                                static_cast<float>(s.slot(3).as_num()),
                                                                static_cast<float>(s.slot(4).as_num()),
                                                                static_cast<float>(s.slot(5).as_num()),
                                                                color);
        });

        s.bind("static tea/graphics::Graphics::drawRect(_,_,_,_,_)", [](Tea::Scripting& s) {
            Color color = s.slot(5).get_native_type<Color>();
            s.get_engine().get_module<Renderer>()->draw_rect(static_cast<float>(s.slot(1).as_num()),
                                                             static_cast<float>(s.slot(2).as_num()),
                                                             static_cast<float>(s.slot(3).as_num()),
                                                             static_cast<float>(s.slot(4).as_num()),
                                                             color);
        });

        s.bind("static tea/graphics::Graphics::setTexture(_)", [](Tea::Scripting& s) {
            s.get_engine().get_module<Renderer>()->set_texture(s.slot(1).get_native_type<std::shared_ptr<Texture>>());
        });

        s.bind("static tea/graphics::Texture::load(_)", [](Tea::Scripting& s) {
            auto filename = s.slot(1).as_str();

            auto image = s.get_engine().get_assets().load_image(filename);
            if (!image) {
                s.error("Could not find file.");
                return;
            }

            auto tex = Texture::create(*image);
            s.slot(0).set_native_type(std::move(tex), 0);
        });

        s.bind("tea/graphics::Texture::width", [](Tea::Scripting& s) {
            auto w = s.slot(0).get_native_type<std::shared_ptr<Texture>>()->get_width();
            s.slot(0).set_num(w);
        });

        s.bind("tea/graphics::Texture::height", [](Tea::Scripting& s) {
            auto h = s.slot(0).get_native_type<std::shared_ptr<Texture>>()->get_height();
            s.slot(0).set_num(h);
        });

        s.bind("static tea/graphics::Color::hex(_)", [](Tea::Scripting& s) {
            std::string str = s.slot(1).as_str();

            s.error("invalid argument 'hex': must be a hexadecimal RGB or RGBA color code (eg. #ffffff or #00abffcc)");
        });

        s.bind("static tea/graphics::Color::rgba(_,_,_,_)", [](Tea::Scripting& s) {
            float r = static_cast<float>(s.slot(1).as_num());
            float g = static_cast<float>(s.slot(2).as_num());
            float b = static_cast<float>(s.slot(3).as_num());
            float a = static_cast<float>(s.slot(4).as_num());

            s.slot(0).set_native_type(Color::from_rgba_float(r, g, b, a), 0);
        });

        s.bind("static tea/graphics::Color::rgba(_)", [](Tea::Scripting& s) {
            uint32_t rgba = static_cast<uint32_t>(s.slot(1).as_num());

            s.slot(0).set_native_type(Color::from_rgba(rgba), 0);
        });

        s.bind("static tea/graphics::Color::rgb(_,_,_)", [](Tea::Scripting& s) {
            uint8_t r = static_cast<uint8_t>(s.slot(1).as_num());
            uint8_t g = static_cast<uint8_t>(s.slot(2).as_num());
            uint8_t b = static_cast<uint8_t>(s.slot(3).as_num());

            s.slot(0).set_native_type(Color::from_rgb(r, g, b), 0);
        });

        s.bind("static tea/graphics::Color::rgb(_)", [](Tea::Scripting& s) {
            uint32_t rgb = static_cast<uint32_t>(s.slot(1).as_num());

            s.slot(0).set_native_type(Color::from_rgb(rgb), 0);
        });

        s.bind("static tea/graphics::Color::hex(_)", [](Tea::Scripting& s) {
            std::string hex = s.slot(1).as_str();

            try {
                s.slot(0).set_native_type(Color::from_hex(hex), 0);
            } catch (const std::invalid_argument&) {
                s.error(
                    "invalid argument 'hex': must be a hexadecimal RGB or RGBA color code (eg. #ffffff or #00abffcc)");
            }
        });

        s.bind("tea/graphics::Color::r", [](Tea::Scripting& s) {
            Color c = s.slot(0).get_native_type<Color>();
            s.slot(0).set_num(c.r);
        });

        s.bind("tea/graphics::Color::g", [](Tea::Scripting& s) {
            Color c = s.slot(0).get_native_type<Color>();
            s.slot(0).set_num(c.g);
        });

        s.bind("tea/graphics::Color::b", [](Tea::Scripting& s) {
            Color c = s.slot(0).get_native_type<Color>();
            s.slot(0).set_num(c.b);
        });

        s.bind("tea/graphics::Color::a", [](Tea::Scripting& s) {
            Color c = s.slot(0).get_native_type<Color>();
            s.slot(0).set_num(c.a);
        });
    }

    void bind_input(Scripting& s) {
        s.bind("static tea/input::Keyboard::isDown(_)", [](Scripting& s) {
            auto input = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Input::Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_down(keycode));
        });

        s.bind("static tea/input::Keyboard::isUp(_)", [](Scripting& s) {
            auto input = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Input::Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_up(keycode));
        });

        s.bind("static tea/input::Keyboard::isPressed(_)", [](Scripting& s) {
            auto input = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Input::Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_pressed(keycode));
        });

        s.bind("static tea/input::Keyboard::isReleased(_)", [](Scripting& s) {
            auto input = s.get_engine().get_module<Input>();
            auto keycode = static_cast<Input::Keycode>(s.slot(1).as_num());
            s.slot(0).set_bool(input->is_key_released(keycode));
        });
    }

    void bind(Scripting& s) {
        bind_graphics(s);
        bind_input(s);
    }
}