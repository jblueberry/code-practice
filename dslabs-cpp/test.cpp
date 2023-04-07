#include "KVStore/KVStore.hpp"
#include <cassert>
#include <iostream>

#define AssertEquals(expected, actual) assert(*expected == *actual)

int main()
{

    daniel::KVStore kvStore;

    auto KeyNotFound = []()
    {
        return std::make_shared<daniel::KeyNotFound>();
    };

    auto PutOk = []()
    {
        return std::make_shared<daniel::PutOk>();
    };

    auto GetResult = [](const std::string &value)
    {
        return std::make_shared<daniel::GetResult>(value);
    };

    auto AppendResult = [](const std::string &value)
    {
        return std::make_shared<daniel::AppendResult>(value);
    };

    using namespace daniel;

    AssertEquals(KeyNotFound(), kvStore.Execute(Get("FOO")));
    AssertEquals(PutOk(), kvStore.Execute(Put("FOO", "BAR")));
    AssertEquals(AppendResult("BARBAZ"),
                 kvStore.Execute(Append("FOO", "BAZ")));
    AssertEquals(AppendResult("BARBAZBAZ"),
                 kvStore.Execute(Append("FOO", "BAZ")));
    AssertEquals(AppendResult("BAR2"),
                 kvStore.Execute(Append("FOO2", "BAR2")));
    AssertEquals(PutOk(), kvStore.Execute(Put("FOO2", "BAZ2")));
    AssertEquals(GetResult("BAZ2"), kvStore.Execute(Get("FOO2")));
    AssertEquals(PutOk(), kvStore.Execute(Put("fizz", "buzz")));
    AssertEquals(GetResult("buzz"), kvStore.Execute(Get("fizz")));
    AssertEquals(GetResult("BARBAZBAZ"), kvStore.Execute(Get("FOO")));
    AssertEquals(AppendResult("BARBAZBAZ[c:1, v:2]"),
                 kvStore.Execute(Append("FOO", "[c:1, v:2]")));
    AssertEquals(GetResult("BARBAZBAZ[c:1, v:2]"),
                 kvStore.Execute(Get("FOO")));
}