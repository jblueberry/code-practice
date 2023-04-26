#pragma once

#include "meta.hpp"
#include <string>
#include <concepts>
#include <unordered_map>
#include <memory>
#include <iostream>

namespace daniel
{
    template <typename T>
    concept StringConvertible = std::convertible_to<T, std::string>;

    class KVStoreCommand : public Command
    {
        template <typename T>
            requires std::derived_from<T, KVStoreCommand>
        friend bool operator==(const T &lhs, const KVStoreCommand &rhs)
        {
            if (typeid(lhs) != typeid(rhs))
                return false;
            return lhs == static_cast<const T &>(rhs);
        };

    private:
        template <typename T>
            requires std::derived_from<T, KVStoreCommand>
        KVStoreCommand(T &&) = delete;

        template <typename T>
            requires std::derived_from<T, KVStoreCommand>
        KVStoreCommand &operator=(T &&) = delete;

    public:
        KVStoreCommand() {}
    };

    class SingleKeyCommand : public KVStoreCommand
    {
        virtual const std::string &Key() const = 0;
    };

    class KVStoreResult : public Result
    {
        template <typename T>
            requires std::derived_from<T, KVStoreResult>
        friend bool operator==(const T &lhs, const KVStoreResult &rhs)
        {
            if (typeid(lhs) != typeid(rhs))
                return false;
            return lhs == static_cast<const T &>(rhs);
        };

    private:
        template <typename T>
            requires std::derived_from<T, KVStoreResult>
        KVStoreResult(T &&) = delete;

        template <typename T>
            requires std::derived_from<T, KVStoreResult>
        KVStoreResult &operator=(T &&) = delete;

    public:
        KVStoreResult() {}
    };

    class Get : public SingleKeyCommand
    {
    private:
        std::string key;

    public:
        template <StringConvertible T>
        Get(T &&key) : key(std::forward<T>(key)) {}

        const std::string &Key() const override
        {
            return key;
        }

        bool operator==(const Get &other)
        {
            return key == other.key;
        }
    };

    class Put : public SingleKeyCommand
    {
    private:
        std::string key;
        std::string value;

    public:
        template <StringConvertible T, StringConvertible U>
        Put(T &&key, U &&value) : key(std::forward<T>(key)), value(std::forward<U>(value)) {}

        const std::string &Key() const override
        {
            return key;
        }

        const std::string &Value() const
        {
            return value;
        }

        bool operator==(const Put &other)
        {
            return key == other.key && value == other.value;
        }
    };

    class Append : public SingleKeyCommand
    {
    private:
        std::string key;
        std::string value;

    public:
        template <StringConvertible T, StringConvertible U>
        Append(T &&key, U &&value) : key(std::forward<T>(key)), value(std::forward<U>(value)) {}

        const std::string &Key() const override
        {
            return key;
        }

        const std::string &Value() const
        {
            return value;
        }

        bool operator==(const Append &other)
        {
            return key == other.key && value == other.value;
        }
    };

    class GetResult : public KVStoreResult
    {
    private:
        std::string value;

    public:
        template <StringConvertible T>
        GetResult(T &&value) : value(std::forward<T>(value)) {}

        const std::string &Value() const
        {
            return value;
        }

        bool operator==(const GetResult &other) const
        {
            return value == other.value;
        }
    };

    class PutOk : public KVStoreResult
    {
    public:
        bool operator==(const PutOk &other) const
        {
            return true;
        }
    };

    class AppendResult : public KVStoreResult
    {
    private:
        std::string value;

    public:
        template <StringConvertible T>
        AppendResult(T &&value) : value(std::forward<T>(value)) {}

        const std::string &Value()
        {
            return value;
        }

        bool operator==(const AppendResult &other) const
        {
            return value == other.value;
        }
    };

    class KeyNotFound : public KVStoreResult
    {
    public:
        bool operator==(const KeyNotFound &other) const
        {
            return true;
        }
    };

    class KVStore : public Application
    {
    private:
        std::unordered_map<std::string, std::string> store_;

    public:
        KVStore() : store_() {}

        std::shared_ptr<Result> Execute(const Command &command) override
        {
            // check if command is a KVStoreCommand
            if (const KVStoreCommand *kvCommand = dynamic_cast<const KVStoreCommand *>(&command))
            {
                // check if command is a Get
                if (const Get *getCommand = dynamic_cast<const Get *>(kvCommand))
                {
                    return Execute(*getCommand);
                }
                // check if command is a Put
                else if (const Put *putCommand = dynamic_cast<const Put *>(kvCommand))
                {
                    return Execute(*putCommand);
                }
                // check if command is a Append
                else if (const Append *appendCommand = dynamic_cast<const Append *>(kvCommand))
                {
                    return Execute(*appendCommand);
                }
                else
                {
                    throw std::runtime_error("Unknown KVStoreCommand");
                }
            }
            else
            {
                throw std::runtime_error("Unknown Command");
            }
        }

        std::shared_ptr<KVStoreResult> Execute(const Get &command)
        {
            auto it = store_.find(command.Key());
            if (it == store_.end())
            {
                return std::make_shared<KeyNotFound>();
            }
            else
            {
                return std::make_shared<GetResult>(it->second);
            }
        }

        std::shared_ptr<KVStoreResult> Execute(const Put &command)
        {
            store_[command.Key()] = command.Value();
            return std::make_shared<PutOk>();
        }

        std::shared_ptr<KVStoreResult> Execute(const Append &command)
        {
            auto it = store_.find(command.Key());
            if (it == store_.end())
            {
                store_[command.Key()] = command.Value();
                return std::make_shared<AppendResult>(command.Value());
            }
            else
            {
                it->second += command.Value();
                return std::make_shared<AppendResult>(it->second);
            }
        }
    };
}