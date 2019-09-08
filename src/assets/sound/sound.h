#ifndef TEA_SOUND_H
#define TEA_SOUND_H

#include <memory>
#include <vector>

#include "../asset.h"

namespace Tea {
    /**
     * Represents a sound file. Does not guarantee whether the file is preloaded or streamed.
     */
    class Sound: public Asset {
    public:
        virtual float get_length() const = 0;
        virtual uint32_t get_sample_count() const = 0;
        virtual uint32_t get_sample_rate() const = 0;
    };
}


#endif
