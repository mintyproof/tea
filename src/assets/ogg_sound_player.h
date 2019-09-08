#ifndef TEA_OGG_SOUND_PLAYER_H
#define TEA_OGG_SOUND_PLAYER_H

#include "sound_player.h"
#include "ogg_sound.h"

struct stb_vorbis;

namespace Tea {
    class OggSoundPlayer: public SoundPlayer {
    public:
        explicit OggSoundPlayer(OggSound &sound);
        ~OggSoundPlayer();

        size_t get_samples(size_t count, int channels, int16_t *out) override;
        size_t get_samples(size_t count, int channels, float *out) override;
        bool is_finished() override;
    private:
        stb_vorbis* vorbis;
    };
}

#endif
