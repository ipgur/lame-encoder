//
// Created by igur on 2019-02-18.
//

#include "SimpleThreadPool.h"
#include "LameEncoder.h"

#include <string>
#include <iostream>
#include <lame/lame.h>
#include <utils.h>
#include <thread>
#include <memory>
#include <cstdint>
#include <future>

using namespace std::chrono_literals;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " WAV_FOLDER" << std::endl;
        return 1;
    }

    const std::string folder(argv[1]);

    if (!utils::dirExists(folder)) {
        return 1;
    }

    std::vector<std::string> wavFiles;
    utils::read_directory(folder, wavFiles);
    int numThreads = std::thread::hardware_concurrency();
    std::cout << "Number of threads to pump events: " << numThreads << std::endl;
    auto simpleThreadPool = std::make_unique<SimpleThreadPool>(numThreads);
    LameEncoder lameEncoder;

    for (const auto &wav : wavFiles) {
        simpleThreadPool->schedule(std::bind(&LameEncoder::lame_encode, &lameEncoder, folder + wav,
                                             folder + utils::getMp3FromWav(wav)));
    }

    auto future = std::async(std::launch::async, [&](){
        while(lameEncoder.getProcessedWavFiles() != wavFiles.size()) {
            std::cout << "Progress " << lameEncoder.getProcessedWavFiles() * 100 / wavFiles.size()  << "% still working ..." << std::endl;
            std::this_thread::sleep_for(2s);
        }
    });

    // wait till all jobs complete
    simpleThreadPool.reset();

    future.get();

    std::cout << "100% Done. Totally processed wav file conversions " << lameEncoder.getProcessedWavFiles() << std::endl;
    return 0;
}