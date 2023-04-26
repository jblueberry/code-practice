#pragma once

#include <concepts>
#include <memory>

namespace daniel
{
    class Timer
    {
        virtual ~Timer() = default;
    };
    
    class Message
    {
        virtual ~Message() = default;
    };

    class Result
    {
    public:
        virtual ~Result() = default;
    };

    class Command
    {
    public:
        virtual bool ReadOnly()
        {
            return false;
        }
    };

    class Application
    {
    public:
        virtual std::shared_ptr<Result> Execute(const Command &) = 0;
    };

    class Address
    {
    private:
        std::string address_;

    public:
        Address(std::string address) : address_(std::move(address)) {}
        bool operator==(const Address &other) const
        {
            return address_ == other.address_;
        }

        friend struct std::hash<Address>;
    };
}

namespace std
{
    // hash function for Address
    template <>
    struct hash<daniel::Address>
    {
        size_t operator()(const daniel::Address &address) const
        {
            return std::hash<std::string>()(address.address_);
        }
    };
}