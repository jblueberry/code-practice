#include <iostream>
#include "KVStore/KVStore.hpp"
#include "AMO/AMOApplication.hpp"

int main()
{
    using namespace daniel;

    auto kvStore = std::make_unique<KVStore>();

    auto amo = std::make_unique<AMOApplication<KVStore>>(std::move(kvStore));

    auto amo_command = AMOCommand(std::make_shared<Address>("junhui"), std::make_shared<Put>("FOO", "bar"), 1);

    auto result = amo->Execute(amo_command);

    // convert result to AMOResult
    auto *amo_result = dynamic_cast<AMOResult *>(result.get());
    if (amo_result == nullptr)
        throw std::runtime_error("result is not an AMOResult");

    std::cout << "seq: " << amo_result->seq << std::endl;
    std::cout << typeid(*amo_result->result).name() << std::endl;
}