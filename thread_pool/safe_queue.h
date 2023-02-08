#pragma once

#include <queue>
#include <mutex>

template <typename T>
class SafeQueue
{
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;

public:
    SafeQueue() {}
    SafeQueue(SafeQueue &&other)
    {
        std::lock_guard<std::mutex> lock(other.m_mutex);
        m_queue = std::move(other.m_queue);
    }
    ~SafeQueue() {}
    SafeQueue(const SafeQueue &) = delete;

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
    int size()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    void
    enqueue(T &t)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.emplace(t);
    }

    void
    enqueue(T &&t)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.emplace(std::move(t));
    }

    bool
    dequeue(T &t)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty())
            return false;
        t = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }
};