#pragma once
#include "../Meta.hpp"
#include <unordered_map>

namespace daniel
{
    struct AMOCommand : public Command
    {
        std::shared_ptr<Address> address;
        std::shared_ptr<Command> command;
        int seq;

        AMOCommand(std::shared_ptr<Address> address, std::shared_ptr<Command> command, int seq) : address(std::move(address)), command(std::move(command)), seq(seq) {}
    };

    struct AMOResult : public Result
    {
        std::shared_ptr<Result> result;
        int seq;

        AMOResult(std::shared_ptr<Result> result, int seq) : result(std::move(result)), seq(seq) {}
    };

    template <typename T>
        requires std::derived_from<T, Application>
    class AMOApplication : public Application
    {
    private:
        std::unique_ptr<T> application_;
        std::unordered_map<Address, int> nextSeqMap_;
        std::unordered_map<Address, std::shared_ptr<AMOResult>> pendingResults_;

    public:
        AMOApplication(std::unique_ptr<T> application) : application_(std::move(application)) {}

        std::shared_ptr<Result> Execute(const Command &command) override
        {
            std::cout << "AMOApplication::Execute" << std::endl;
            auto *amoCommand = dynamic_cast<const AMOCommand *>(&command);
            if (amoCommand == nullptr)
                // throw exception
                throw std::runtime_error("command is not an AMOCommand");

            if (AlreadyExecuted(*amoCommand))
            {
                auto it = pendingResults_.find(*amoCommand->address);
                if (it == pendingResults_.end())
                    // throw exception
                    throw std::runtime_error("pending result not found");
                return it->second;
            }

            std::cout << "AMOApplication::Execute: executing command" << std::endl;

            auto result = application_->Execute(*(amoCommand->command));

            std::cout << "AMOApplication::Execute: command executed" << std::endl;
            pendingResults_[*amoCommand->address] = std::make_shared<AMOResult>(result, amoCommand->seq);
            nextSeqMap_[*amoCommand->address] = amoCommand->seq + 1;

            return std::make_shared<AMOResult>(result, amoCommand->seq);
        }

    private:
        bool AlreadyExecuted(const AMOCommand &command)
        {
            auto it = nextSeqMap_.find(*command.address);
            if (it == nextSeqMap_.end())
                return false;
            return it->second > command.seq;
        }
    };
}
