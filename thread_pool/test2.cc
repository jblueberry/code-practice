#include <atomic>
#include <thread>
#include <cassert>

std::atomic<int> x, y, z;

void f1() {
    x.store(1, std::memory_order_relaxed);
    if (y.load(std::memory_order_relaxed))
        z++;
}

void f2() {
    y.store(1, std::memory_order_relaxed);
    if (x.load(std::memory_order_relaxed))
        z++;
}

int main() {
    std::thread t1(f1);
    std::thread t2(f2);
    t1.join();
    t2.join();
    assert(z != 0);
    // 这个 assert 会失败吗？
}