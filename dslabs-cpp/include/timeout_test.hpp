#include <gtest/gtest.h>
#include <future>
#include <pthread.h>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace daniel
{
#define TEST_TIMEOUT(test_suite_name, test_name, million_seconds, f) \
    TEST(test_suite_name, test_name)                                 \
    {                                                                \
        test_timeout<million_seconds>(f);                            \
    }

    class KillableProcess
    {
        struct shm_remove
        {
            shm_remove()
            {
                boost::interprocess::shared_memory_object::remove("dslabs");
            }
            ~shm_remove()
            {
                boost::interprocess::shared_memory_object::remove("dslabs");
            }
        };

    public:
        KillableProcess(std::function<void()> f) : f_(f)
        {
            auto shm = boost::interprocess::shared_memory_object(
                boost::interprocess::create_only, "dslabs", boost::interprocess::read_write);
            shm.truncate(1);
            region_ = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
            auto flag = static_cast<bool *>(region_.get_address());
            *flag = false;
        }

        void Run()
        {
            // create a new process to run the function, not thread
            auto pid = fork();
            if (pid == 0)
            {
                f_();

                // set the flag to true
                auto flag = static_cast<bool *>(region_.get_address());
                *flag = true;
                exit(0);
            }
            else
            {
                handle_ = pid;
            }
        }

        bool Finished()
        {
            auto flag = static_cast<bool *>(region_.get_address());
            return *flag;
        }

        void Stop()
        {
            if (handle_ != -1)
            {
                kill(handle_, SIGABRT);
            }
        }

    private:
        std::function<void()> f_;
        pid_t handle_ = -1;
        shm_remove remover_;
        boost::interprocess::mapped_region region_;
    };

    template <size_t million_seconds, typename F>
        requires std::invocable<F>
    void test_timeout(F &&f)
    {
        // create a sub process to run the function

        KillableProcess process(f);
        process.Run();
        std::this_thread::sleep_for(std::chrono::milliseconds(million_seconds));

        if (!process.Finished())
        {
            process.Stop();
            FAIL() << "Test timeout " << million_seconds << "ms";
        }
        else
        {
            SUCCEED();
        }
    }

}