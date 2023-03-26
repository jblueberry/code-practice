#include <iostream>
#include <tuple>
#include <vector>
#include <memory>
#include <unordered_set>

// convert a 64-bit virtual address to 4 9-bit page numbers
auto virtual_address_to_page_numbers(uint64_t virtual_address)
{
    virtual_address >>= 12;
    auto p4 = virtual_address & 0x1FF;
    virtual_address >>= 9;
    auto p3 = virtual_address & 0x1FF;
    virtual_address >>= 9;
    auto p2 = virtual_address & 0x1FF;
    virtual_address >>= 9;
    auto p1 = virtual_address & 0x1FF;
    return std::make_tuple(p1, p2, p3, p4);
}

using P4 = uint64_t;
using P4Table = std::vector<P4>;
using P3Table = std::vector<std::shared_ptr<P4Table>>;
using P2Table = std::vector<std::shared_ptr<P3Table>>;
using P1Table = std::vector<std::shared_ptr<P2Table>>;

void insert(P1Table &p1_table, uint64_t virtual_address)
{
    auto [p1, p2, p3, p4] = virtual_address_to_page_numbers(virtual_address);

    if (p1_table[p1] == nullptr)
    {
        p1_table[p1] = std::make_shared<P2Table>(512);
    }
    auto &p2_table = *p1_table[p1];
    if (p2_table[p2] == nullptr)
        p2_table[p2] = std::make_shared<P3Table>(512);
    auto &p3_table = *p2_table[p2];
    if (p3_table[p3] == nullptr)
        p3_table[p3] = std::make_shared<P4Table>(512);
    auto &p4_table = *p3_table[p3];
    p4_table[p4] = 1;
}

auto countPages(P1Table *p1_table)
{
    int p1_count = 0;
    int p2_count = 0;
    int p3_count = 0;
    int p4_count = 0;

    if (p1_table == nullptr)
        return std::make_tuple(p1_count, p2_count, p3_count, p4_count);

    p1_count = 1;

    std::unordered_set<P2Table *> p2_set;
    std::unordered_set<P3Table *> p3_set;
    std::unordered_set<P4Table *> p4_set;

    for (auto &p2 : *p1_table)
    {
        if (p2 == nullptr)
            continue;

        if (p2_set.find(p2.get()) == p2_set.end())
        {
            p2_count++;
            p2_set.insert(p2.get());

            for (auto &p3 : *p2)
            {
                if (p3 == nullptr)
                    continue;

                if (p3_set.find(p3.get()) == p3_set.end())
                {
                    p3_count++;
                    p3_set.insert(p3.get());

                    for (auto &p4 : *p3)
                    {
                        if (p4 == nullptr)
                            continue;

                        if (p4_set.find(p4.get()) == p4_set.end())
                        {
                            p4_count++;
                            p4_set.insert(p4.get());
                        }
                    }
                }
            }
        }
    }

    return std::make_tuple(p1_count, p2_count, p3_count, p4_count);
}

int main()
{
    P1Table p1_table(512);

    int num;
    std::cin >> num;

    int page_num = 0;

    while (num > 0)
    {
        uint64_t low, high;

        std::cin >> std::hex >> low >> high;
        page_num += (high - low) / 4096;

        for (uint64_t i = low; i < high; i += 4096)
        {
            insert(p1_table, i);
        }

        num--;
    }

    auto [p1_count, p2_count, p3_count, p4_count] = countPages(&p1_table);
    std::cout << p1_count << " " << p2_count << " " << p3_count << " " << p4_count << std::endl;
    std::cout << page_num << std::endl;
}