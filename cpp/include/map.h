#pragma once
#include <optional>

namespace junhui
{
    template <class K, class V>
    class Map
    {
    protected:
        using KV = std::pair<K, V>;

    public:
        virtual std::optional<V> Lookup(const K &) = 0;
        virtual void Update(const KV &) = 0;
    };

    template <class Key, class Value>
    class WRRMBNTMMap : public Map<Key, Value>
    {
        using Data = std::pair<Map<Key, Value> *, unsigned>;
        Data data_;

    public:
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
            Map<Key, Value> *last = nullptr;

            do
            {
                old.first = data_.first;
                if (last != old.first)
                {
                    if (fresh.first)
                        delete fresh.first;
                    fresh.first = new Map<Key, Value>(*old.first);
                    fresh.first->insert(key, value);
                    last = old.first;
                }
            } while (!CAS(&data_, old, fresh));

            // delete it confidently
            delete old.first;
        }
    };
}
