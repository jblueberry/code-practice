#include <thread>
#include <iostream>
#include <future>
#include <signal.h>

int main()
{
    // create a thread that will run a loop, each will sleep for 5 seconds
    std::atomic_bool finished = false;
    auto thread = std::thread([&finished]()
                              {
                                  for (int i = 0; i < 1; i++)
                                  {
                                      std::cout << "thread " << i << std::endl;
                                      std::this_thread::sleep_for(std::chrono::seconds(2));
                                  }
                                  finished = true; });
    std::this_thread::sleep_for(std::chrono::seconds(3));

    if (!finished)
    {
        std::cout << "thread is still running" << std::endl;
        std::cout << "send SIGINT to the thread" << std::endl;
        pthread_kill(thread.native_handle(), SIGABRT);
    }
    else
    {
        std::cout << "thread is finished" << std::endl;
    }

    thread.join();

    return 0;
}