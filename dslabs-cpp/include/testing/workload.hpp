#pragma once

#include <vector>
#include <memory>
#include "../meta.hpp"

namespace daniel
{
    class WorkLoad
    {
        class WorkLoadBuilder
        {
        private:
            std::vector<std::shared_ptr<Command>> commands_;
            std::vector<std::shared_ptr<Result>> results_;
            bool finite_ = true;

        public:
            static WorkLoadBuilder Infinite()
            {
                WorkLoadBuilder builder;
                builder.finite_ = false;
                return builder;
            }

            WorkLoadBuilder &AddCommand(std::vector<Command> &&commands)
            {
                commands_.insert(commands_.end(), commands.begin(), commands.end());
                return *this;
            }

            WorkLoadBuilder &AddResult(std::vector<Result> &&results)
            {
                results_.insert(results_.end(), results.begin(), results.end());
                return *this;
            }
        };
    };
}