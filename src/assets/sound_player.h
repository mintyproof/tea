#ifndef TEA_SOUND_PLAYER_H
#define TEA_SOUND_PLAYER_H

#include <cstddef>
#include <cstdint>

namespace Tea {
    /**
     * Stateful "sound player" instance. Only "knows" how to play one instance of one sound, and will keep track of
     * where it is in the playback.
     */
    class SoundPlayer {
    public:
        virtual size_t get_samples(size_t count, int channels, int16_t* out) = 0;
        virtual size_t get_samples(size_t count, int channels, float* out) = 0;

        virtual bool is_finished() = 0;
    };
}

#endif