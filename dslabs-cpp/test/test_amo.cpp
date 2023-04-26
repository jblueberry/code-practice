#include <iostream>
#include "kv_store.hpp"
#include "amo_application.hpp"

class Test
{
public:
    std::string name;
    // moveing and copying constructor and assignment operator

public:
    Test(Test &&)
    {
        std::cout << "moveing constructor" << std::endl;
    }
    Test(const Test &other)
    {
        // copy the name
        name = other.name;
        std::cout << "copying constructor" << std::endl;
    }
    Test &operator=(Test &&)
    {
        std::cout << "moveing assignment operator" << std::endl;
        return *this;
    }
    Test &operator=(const Test &)
    {
        std::cout << "copying assignment operator" << std::endl;
        return *this;
    }

    ~Test()
    {
        std::cout << "deconstructor " << "address: " << this << std::endl;
    }

    Test(std::string name) : name(name) {
        std::cout << "constructor " << "address: " << this << std::endl;
        std::cout << "address of name: " << &this->name << std::endl;
    }

    const std::string &get_name()
    {
        std::cout << "address of name: " << &name << std::endl;
        return name;
    }
};

Test &get_test1()
{
    auto junhui = std::make_shared<Test>("junhui");
    return *junhui;
}

Test &get_test2()
{
    auto junhui = std::make_shared<Test>("zhu");
    auto str_ptr = &junhui->name;
    // cast this pointer to long pointer
    // and set the value to 0x4141414141414141
    // which is the hex value of 'A'
    *reinterpret_cast<long*>(str_ptr) = 0x4141414141414141;
}

#include <vector>

int main()
{
    Test &x1 = get_test1();
    

    auto x2 = get_test2();

    std::cout << "x1 address: " << &x1 << std::endl;
    // std::cout << "x2 address: " << &x2 << std::endl;

    // print two name
    std::cout << "x1 name: " << x1.get_name() << std::endl;
    // std::cout << "x2 name: " << x2.get_name() << std::endl;
    return 0;
}