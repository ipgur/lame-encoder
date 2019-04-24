//
// Created by igur on 2019-02-18.
//

#ifndef LAME_ENCODER_SIMPLEPOOL_H
#define LAME_ENCODER_SIMPLEPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>


class SimpleThreadPool final {

    public:
        explicit SimpleThreadPool(size_t threads);
        ~SimpleThreadPool();

        SimpleThreadPool(const SimpleThreadPool &) = delete;

        void initializeWithThreads(size_t threads);
        void schedule(const std::function<void()> &);

    private:
        std::vector<std::thread> m_workers;
        std::queue<std::function<void()>>  m_taskQueue;
        std::atomic_uint m_taskCount;
        std::mutex m_mutex;
        std::condition_variable m_condition;
        std::atomic_bool m_stop;
};

#endif //LAME_ENCODER_SIMPLEPOOL_H
