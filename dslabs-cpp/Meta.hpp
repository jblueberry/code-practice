#pragma once

#include <concepts>
#include <iostream>
// define an interface named Application, has a pure virtual function named execute
// What is inteface in C++?
// An interface is a class that contains only pure virtual functions.

namespace daniel
{
    class _Comparable
    {
    public:
        virtual bool operator==(const _Comparable &other) const = 0;
    };

    template <typename Derived>
    class Comparable: public _Comparable
    {
    public:
        bool operator==(const _Comparable &other) const override
        {
            std::cout << "comparing " << typeid(*this).name() << " and " << typeid(other).name() << std::endl;
            if (const auto *derived = dynamic_cast<const Derived *>(&other))
            {
                return static_cast<const Derived *>(this)->operator==(*derived);
            }
            else
            {
                return false;
            }
        }
    };

    class Result
    {
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

        virtual Result Execute(Command) = 0;
    };

}