#include "map.h"
#include <optional>
#include <cassert>

int main()
{
    junhui::StdMap<int, int> map;
    // runtime assert
    assert(map.Lookup(1) == std::nullopt);
    map.Update(1, 2);
    assert(map.Lookup(1) == 2);
}