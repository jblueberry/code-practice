#include <iostream>
#include <typeinfo>
#include <concepts>
#include <memory>

class B;

class Result
{
private:
    template <typename T>
        requires std::derived_from<T, Result>
    Result(T &&) = delete;

    template <typename T>
        requires std::derived_from<T, Result>
    Result &operator=(T &&) = delete;

    // Result(B &&) = delete;

public:
    Result() {}
    // make it a pure virtual class
    virtual ~Result() = default;

    template <typename T>
        requires std::derived_from<T, Result>
    friend bool operator==(const T &lhs, const Result &rhs)
    {
        std::cout << "comparing " << typeid(T).name() << " and " << typeid(Result).name() << std::endl;
        // try to dynamic cast to the type of lhs
        auto *casted = dynamic_cast<const T *>(&rhs);
        if (casted == nullptr)
        {
            std::cout << "casted is null" << std::endl;
            return false;
        }
        return lhs == *casted;
    };
};

class A : public Result
{
private:
    int a;

public:
    // explicitly initialize the base class
    A(int a) : a(a) {}

    bool operator==(const A &other) const
    {
        std::cout << "comparing A and A" << std::endl;
        return this->a == other.a;
    }
};

class B : public Result
{
private:
    int a;

public:
    B(int a) : a(a)
    {
        std::cout << "B constructor" << std::endl;
    }

    bool operator==(const B &other) const
    {
        std::cout << "comparing B and B" << std::endl;
        return this->a == other.a;
    }
};

class Base
{
public:
    int x;

    Base(int x): x(x) {}
};

class Derived : public Base
{
public:
    int y;

public:
    Derived(int x, int y): Base(x), y(y) {}
};

int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>(1, 2);

    std::shared_ptr<Result> result = std::make_shared<B>(2);
    B b(2);
    std::cout << (b == *result);
    return 0;
}