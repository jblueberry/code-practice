#include "map.h"

template <class K, class V>
class MapImpl : public junhui::Map<K, V>
{
    // using KV = std::pair<K, V>;
public:
    std::optional<V> Lookup(const K &key) { return std::nullopt; }
    void Update(const KV &kv) {}
};
int main()
{
    MapImpl<int, int> map;
}