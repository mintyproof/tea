#ifndef TEA_OGG_SOUND_H
#define TEA_OGG_SOUND_H

#include "sound.h"

namespace Tea {
    class OggSound: public Sound {
        friend class OggSoundPlayer;
    public:
        explicit OggSound(std::vector<uint8_t>&& data);

        float get_length() const override;
        uint32_t get_sample_count() const override;
        uint32_t get_sample_rate() const override;
    private:
        std::vector<uint8_t> ogg_data;

        uint8_t channels;
        uint32_t sample_rate;
        uint32_t sample_count;
    };
}


#endif