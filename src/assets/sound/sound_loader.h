#ifndef TEA_SOUND_LOADER_H
#define TEA_SOUND_LOADER_H

#include <memory>
#include <vector>

#include "sound.h"

namespace Tea {
    class SoundLoader {
    public:
        static std::unique_ptr<Sound> load_ogg(std::vector<uint8_t>&& data);
    };
}


#endif