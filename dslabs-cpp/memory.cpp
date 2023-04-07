#include <memory>
#include <iostream>
#include <string>

struct B
{
    int x;
};

struct A : public B
{
    std::string name;
    A(std::string name) : name(name) {}
};

const B &getA()
{
    auto p = std::make_shared<A>("hello");
    return *p;
}

int main()
{
    auto b = getA();
    int x;
    int y;
    int z;

    // convert b to A
    auto a = static_cast<const A &>(b);

    std::cout << a.name << std::endl;
}