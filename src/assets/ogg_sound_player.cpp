#include "ogg_sound_player.h"

#include <fmt/core.h>
#include <stb_vorbis.c>

Tea::OggSoundPlayer::OggSoundPlayer(Tea::OggSound &sound) {
    int error = 0;
    this->vorbis = stb_vorbis_open_memory(&sound.ogg_data.front(), sound.ogg_data.size(), &error, nullptr);
    if (!this->vorbis)
        throw std::runtime_error(fmt::format("Error opening OGG file (code {})", error));
}

Tea::OggSoundPlayer::~OggSoundPlayer() {
    // malloced inside stb_vorbis_open_memory, gotta free here
    free(this->vorbis);
}

size_t Tea::OggSoundPlayer::get_samples(size_t count, int channels, int16_t *out) {
    return stb_vorbis_get_samples_short_interleaved(this->vorbis, channels, out, count * channels);
}

size_t Tea::OggSoundPlayer::get_samples(size_t count, int channels, float *out) {
    return stb_vorbis_get_samples_float_interleaved(this->vorbis, channels, out, count * channels);
}

bool Tea::OggSoundPlayer::is_finished() {
    // todo
    return false;
}