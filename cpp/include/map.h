#pragma once
#include <optional>
#include <unordered_map>

namespace junhui
{
    template <class K, class V>
    class Map
    {
    public:
        virtual std::optional<V> Lookup(const K &) = 0;
        virtual void Update(const K &, const V &) = 0;
    };

    template <class K, class V>
    class StdMap : public Map<K, V>
    {
    private:
        std::unordered_map<K, V> map_;

    public:
        StdMap() = default;
        StdMap(const StdMap & other) : map_(other.map_) {}
        std::optional<V> Lookup(const K &key) override
        {
            auto it = map_.find(key);
            if (it == map_.end())
                return std::nullopt;
            return it->second;
        }

        void Update(const K &key, const V &value) override
        {
            map_[key] = value;
        }
    };

    template <class Key, class Value>
    class WRRMBNTMMap : public Map<Key, Value>
    {
        using InternalMap = StdMap<Key, Value>;
        using Data = std::pair<InternalMap *, unsigned>;
        Data data_;

    public:
        WRRMBNTMMap() : data_(new InternalMap(), 1) {}
        Value Lookup(const Key &key)
        {
            Data old;
            Data fresh;
            do
            {
                old = data_;
                fresh = old;
                ++fresh.second;
            } while (!CAS(&data, old, fresh));

            Value temp = (*fresh.first)[k];
            do
            {
                old = data_;
                fresh = old;
                --fresh.second;
            } while (!CAS(&data_, old, fresh));
            return temp;
        }

        void Update(const Key &key, const Value &value)
        {
            Data old;
            Data fresh;
            old.second = 1;
            fresh.first = nullptr;
            fresh.second = 1;
            StdMap<Key, Value> *last = nullptr;

            do
            {
                old.first = data_.first;
                if (last != old.first)
                {
                    if (fresh.first)
                        delete fresh.first;
                    fresh.first = new StdMap<Key, Value>(*old.first);
                    fresh.first->insert(key, value);
                    last = old.first;
                }
            } while (!CAS(&data_, old, fresh));

            // delete it confidently
            delete old.first;
        }
    };
}
