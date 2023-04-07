#pragma once

#include <concepts>
#include <iostream>
// define an interface named Application, has a pure virtual function named execute
// What is inteface in C++?
// An interface is a class that contains only pure virtual functions.

namespace daniel
{
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
        virtual Result Execute(Command) = 0;
    };

}