#include "ogg_sound.h"

#include <fmt/core.h>
// #including a C file lol
#include <stb_vorbis.c>

Tea::OggSound::OggSound(std::vector<uint8_t> &&data): ogg_data(std::move(data)) {
    // Briefly open and scan file to get relevant metrics

    int error = 0;
    stb_vorbis* vorbis = stb_vorbis_open_memory(&ogg_data.front(), ogg_data.size(), &error, nullptr);
    if (!vorbis)
        throw std::runtime_error(fmt::format("Error opening OGG file (code {})", error));

    auto info = stb_vorbis_get_info(vorbis);
    this->channels = info.channels;
    this->sample_rate = info.sample_rate;
    this->sample_count = stb_vorbis_stream_length_in_samples(vorbis);

    // Free it, don't need it anymore
    // Was malloced inside stb_vorbis_open_memory so we gotta free()
    free(vorbis);
}

float Tea::OggSound::get_length() const {
    return this->get_sample_count() / (float) this->get_sample_rate();
}

uint32_t Tea::OggSound::get_sample_count() const {
    return this->sample_count;
}

uint32_t Tea::OggSound::get_sample_rate() const {
    return this->sample_rate;
}