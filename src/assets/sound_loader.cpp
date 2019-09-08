#include "sound_loader.h"
#include "ogg_sound.h"

std::unique_ptr<Tea::Sound> Tea::SoundLoader::load_ogg(std::vector<uint8_t> &&data) {
    return std::unique_ptr<Sound>(new OggSound(std::move(data)));
}
