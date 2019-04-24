//
// Created by igur on 2019-02-18.
//

#include "SimpleThreadPool.h"
#include <chrono>
#include <iostream>


SimpleThreadPool::SimpleThreadPool(size_t threads) : m_workers(),
    m_taskQueue(),
    m_taskCount(0u),
    m_mutex(),
    m_condition(),
    m_stop(false) {
    initializeWithThreads(threads);
}

SimpleThreadPool::~SimpleThreadPool() {
    m_stop = true;
    m_condition.notify_all();

    for (std::thread &w : m_workers) {
        w.join();
    }
}

void SimpleThreadPool::initializeWithThreads(size_t threads) {
    for (size_t i = 0; i < threads; i++) {
        m_workers.emplace_back([this]() -> void {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(m_mutex);
                    m_condition.wait(lock, [this]() -> bool {
                        return !m_taskQueue.empty() || m_stop;
                    });

                    if (m_stop && m_taskQueue.empty()) {
                        return;
                    }

                    task = std::move(m_taskQueue.front());
                    m_taskQueue.pop();
                }
                task();
                m_taskCount--;
            }
        });
    }
}

void SimpleThreadPool::schedule(const std::function<void()> &task) {
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_taskQueue.push(task);
    }
    m_taskCount++;
    m_condition.notify_one();
}