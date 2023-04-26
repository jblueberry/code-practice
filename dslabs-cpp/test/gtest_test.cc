#include "timeout_test.hpp"

TEST_TIMEOUT(TimeoutTest, TestTimeout1, 1000, []() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
});

TEST_TIMEOUT(TimeoutTest, TestTimeout2, 1000, []() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
});