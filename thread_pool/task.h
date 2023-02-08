
#pragma once

#include <future>
#include <functional>
#include <iostream>

template <typename F, typename... Args>
auto submit(F &&f, Args &&...args) -> std::pair<std::function<void()>, std::future<decltype(f(args...))>>
{
    std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

    return std::make_pair([task_ptr]()
                          { (*task_ptr)(); },
                          std::move(task_ptr->get_future()));
}