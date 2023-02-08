#pragma once

#include "safe_queue.h"
#include "task.h"
#include <thread>

template <size_t N>
class ThreadPool
{
private:
    using Task = std::function<void()>;
    SafeQueue<Task> tasks_;
    std::vector<std::thread> threads_;
    bool stop_;
    std::condition_variable cv;
    std::mutex mtx;

    void worker()
    {
        auto pool = this;
        while (true)
        {
            std::unique_lock<std::mutex> lock(pool->mtx);
            if (pool->stop_)
                break;
            Task task;
            if (pool->tasks_.dequeue(task))
            {
                task();
            }
            else
            {
                pool->cv.wait(lock);
            }
        }
    }

public:
    ThreadPool() : stop_(false)
    {

        for (size_t i = 0; i < N; ++i)
        {
            threads_.emplace_back(&ThreadPool::worker, this);
        }
    };

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ~ThreadPool() = default;

    template <typename F, typename... Args>
    auto addTask(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        auto task = submit(std::forward<F>(f), std::forward<Args>(args)...);
        tasks_.enqueue(std::move(task.first));
        cv.notify_one();
        return std::move(task.second);
    }

    void stop()
    {
        stop_ = true;
        cv.notify_all();
        for (auto &thread : threads_)
            thread.join();
    }
};