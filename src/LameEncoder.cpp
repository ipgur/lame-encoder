//
// Created by igur on 2019-02-18.
//

#include "LameEncoder.h"
#include <lame/lame.h>
#include <cstdio>
#include <iostream>
#include <thread>


void LameEncoder::lame_encode(const std::string &input, const std::string &output) {
    size_t read{0};
    int32_t write{0};

    FILE *wav = std::fopen(input.c_str(), "rb");
    FILE *mp3 = std::fopen(output.c_str(), "wb");

    if (!wav) {
        std::cout << "Couldn't open wav file for reading "  << input << std::endl;
        return;
    }

    if (!mp3) {
        std::cout << "Couldn't open mp3 file for writing" << std::endl;
        return;
    }
    std::cout << "["<< std::this_thread::get_id() << "]Encoding " << input << " into " << output << std::endl;
    short int wav_buffer[WAV_BUFFER_SIZE * 2];
    unsigned char mp3_buffer[MP3_BUFFER_SIZE];
    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 8000);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    do {
        read = std::fread(wav_buffer, 2 * sizeof(short int), WAV_BUFFER_SIZE, wav);
        if (read == 0) {
            write = lame_encode_flush(lame, mp3_buffer, MP3_BUFFER_SIZE);
        } else {
            write = lame_encode_buffer_interleaved(lame, wav_buffer, read, mp3_buffer, MP3_BUFFER_SIZE);
        }

        fwrite(mp3_buffer, write, 1, mp3);
    } while (read != 0);

    ++m_processedWavFiles;

    lame_close(lame);
    fclose(mp3);
    fclose(wav);
}

int32_t LameEncoder::getProcessedWavFiles() const {
    return m_processedWavFiles;
}