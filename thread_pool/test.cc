#include <iostream> // std::cout
#include "thread_pool.h"

double sqrt(double x)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return x * x;
}

void f(int a, double b, void *c)
{
    std::cout << a << ":" << b << ":" << c << std::endl;
}

int main()
{
    ThreadPool<5> pool;

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    auto f1 = pool.addTask(sqrt, 2.0);

    auto f2 = pool.addTask(sqrt, 3.0);

    auto f3 = pool.addTask([]
                           {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 1; });

    std::cout << f1.get() << std::endl;
    std::cout << f2.get() << std::endl;
    std::cout << f3.get() << std::endl;

    pool.stop();
}