#ifndef TEA_AUDIO_H
#define TEA_AUDIO_H

#include <cstdint>

#include "../module.h"

typedef unsigned long PaStreamCallbackFlags;
struct PaStreamCallbackTimeInfo;

namespace Tea {
    class Audio: public Module {
    public:
        explicit Audio(Engine& engine);
        ~Audio();

        void pre_update() override;
        void post_update() override;

        uint32_t sample_rate();
    private:
        static int audio_process_callback(const void* input_raw,
                                      void* output_raw,
                                      unsigned long frame_count,
                                      const PaStreamCallbackTimeInfo* timeInfo,
                                      PaStreamCallbackFlags statusFlags,
                                      void* userData);

        // lol voidptr, blame portaudio
        // may be null if audio backend failed, handle this gracefully (dummy impl)
        void* stream;

        uint64_t current_sample;
    };
}

#endif
