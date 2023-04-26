#include "timeout_test.hpp"

namespace daniel
{
    TEST_TIMEOUT(TimeoutTest, TestTimeout1, 2000, []()
                 { std::this_thread::sleep_for(std::chrono::milliseconds(500)); });

    TEST_TIMEOUT(TimeoutTest, TestTimeout2, 3000, []()
                 {
    for (int i = 0; i < 10; i++)
                                  {
                                      std::cout << "thread " << i << std::endl;
                                      std::this_thread::sleep_for(std::chrono::seconds(2));
                                  } });

}