#include "../meta.hpp"

namespace daniel
{
    class MessageEnvelope
    {
    private:
        std::shared_ptr<Address> from_;
        std::shared_ptr<Address> to_;
        std::shared_ptr<Message> message_;

    public:
        MessageEnvelope(const std::shared_ptr<Address> &from, const std::shared_ptr<Address> &to, const std::shared_ptr<Message> &message) : from_(from), to_(to), message_(message) {}
    };

    class TimerEnvelope
    {
    private:
        std::shared_ptr<Address> to_;
        std::shared_ptr<Timer> timer_;

    public:
        TimerEnvelope(const std::shared_ptr<Address> &to, const std::shared_ptr<Timer> &timer) : to_(to), timer_(timer) {}
    };

    class Network
    {
    };
}