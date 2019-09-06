#include "audio.h"

#include <string>

#include <portaudio.h>
#include <cmath>

#include <fmt/core.h>

void validate_pa_call(PaError err, const std::string& prefix) {
    if (err == paNoError) return;
    throw std::runtime_error(fmt::format("{}: {}", prefix, Pa_GetErrorText(err)));
}

#define PI 3.141592653

namespace Tea {
    Audio::Audio(Engine& engine): Module(engine) {
        fmt::print("Initializing audio backend:\n");
        validate_pa_call(Pa_Initialize(), "could not initialize portaudio");

        fmt::print(" - {}\n", Pa_GetVersionText());

        PaError open_stream_err = Pa_OpenDefaultStream(&this->stream, 0, 2, paFloat32,
                44100, paFramesPerBufferUnspecified, audio_process_callback, this);
        if (open_stream_err != paNoError) {
            fmt::print(" - WARN: Could not open default stream: {}\n", Pa_GetErrorText(open_stream_err));
        } else {
            PaDeviceIndex default_output = Pa_GetDefaultOutputDevice();
            const PaDeviceInfo *default_output_info = Pa_GetDeviceInfo(default_output);
            const PaStreamInfo *stream_info = Pa_GetStreamInfo(this->stream);

            fmt::print(" - Default audio device: {}\n", default_output_info->name);
            fmt::print(" - {} Hz, {}ms latency\n", stream_info->sampleRate, stream_info->outputLatency * 1000);
            validate_pa_call(Pa_StartStream(this->stream), "could not start stream");
        }
    }

    Audio::~Audio() {
        // If this returns an error... this is a destructor lol we're fucked
        Pa_Terminate();
    }

    void Audio::pre_update() {}

    void Audio::post_update() {}

    int Audio::audio_process_callback(const void* input_raw,
                                      void* output_raw,
                                      unsigned long frame_count,
                                      const PaStreamCallbackTimeInfo* timeInfo,
                                      PaStreamCallbackFlags statusFlags,
                                      void* userData) {
        // Let's just get these unsafe casts out of the way
        float* output = static_cast<float*>(output_raw);
        Audio* audio = static_cast<Audio*>(userData);

        float freq = 440.0; // A4
        for (uint32_t i = 0; i < frame_count; i++) {
            audio->current_sample++;

            float sample = sin(freq * 2 * PI * audio->current_sample / audio->sample_rate());

            // Two interleaved channels
            *output++ = sample;
            *output++ = sample;
        }

        return paContinue;
    }

    uint32_t Audio::sample_rate() {
        if (!this->stream) return -1;

        const PaStreamInfo *stream_info = Pa_GetStreamInfo(this->stream);
        return static_cast<uint32_t>(stream_info->sampleRate);
    }
}
