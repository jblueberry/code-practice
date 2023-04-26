#include <gtest/gtest.h>
#include <future>

#define TEST_TIMEOUT(test_suite_name, test_name, million_seconds, f) \
    TEST(test_suite_name, test_name)                                 \
    {                                                                \
        test_timeout<million_seconds>(f);                            \
    }

template <size_t million_seconds, typename F>
    requires std::invocable<F>
void test_timeout(F &&f)
{
    // asyncously run the function, if the function does not return in time, kill it and fail the test
    auto future = std::async(std::launch::async, std::forward<F>(f));
    auto status = future.wait_for(std::chrono::milliseconds(million_seconds));
    if (status == std::future_status::timeout)
    {
        FAIL() << "Test timeout after " << million_seconds << " milliseconds";
    } else {
        GTEST_SUCCEED();
    }
}