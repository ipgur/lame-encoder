//
// Created by igur on 2019-02-18.
//

#ifndef LAME_ENCODER_LAMEENCODER_H
#define LAME_ENCODER_LAMEENCODER_H

#include <string>
#include <atomic>
#include <cstdint>

class LameEncoder final {
        static constexpr auto WAV_BUFFER_SIZE = 8192;
        static constexpr auto MP3_BUFFER_SIZE = 8192;
    public:
        LameEncoder() = default;
        LameEncoder(const LameEncoder &) = delete;
        void lame_encode(const std::string &input, const std::string &output);
        int32_t getProcessedWavFiles() const;
    private:
        std::atomic<int32_t> m_processedWavFiles{0};
};

#endif //LAME_ENCODER_LAMEENCODER_H
