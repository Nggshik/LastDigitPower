
/**Task
 * 
 * Instruction: For a given list [x1, x2, x3, ..., xn] compute the last (decimal) digit of x1 ^ (x2 ^ (x3 ^ (... ^ xn)))
 * 
**/

#include <list>
#include <iostream>
#include <array>
#include <cassert>

using namespace std;

constexpr std::array<std::array<int, 4>, 10> value_mod{{{0, 0, 0, 0}, {1, 1, 1, 1}, {2, 4, 8, 6}, {3, 9, 7, 1}, {4, 6, 4, 6}, {5, 5, 5, 5}, {6, 6, 6, 6}, {7, 9, 3, 1}, {8, 4, 2, 6}, {9, 1, 9, 1}}};
constexpr std::array<std::array<int, 4>, 10> power_mod{{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {1, 3, 1, 3}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {1, 3, 1, 3}, {0, 0, 0, 0}, {1, 1, 1, 1}}};

int last_digit_power_mod(int value, int power)
{
    return power_mod[value % 4][power % 4];
}
struct pw_helper
{
    int power = 0;
    bool isMod = false;
};

int last_digit(list<int> array)
{
    if (array.empty())
        return 1;
    if (array.size() == 1)
        return array.back() % 10;

    pw_helper power;
    power.power = array.back();
    array.pop_back();
    auto value = 0;

    while (array.size() > 1)
    {
        value = array.back();
        array.pop_back();

        if (value == 0)
        {
            if (power.isMod)
            {
                power.power = 0;
            }
            else
            {
                power.power = power.power == 0 ? 1 : 0;
            }
            power.isMod = false;
            continue;
        }
        if (value == 1)
        {
            power.power = 1;
            power.isMod = false;
            continue;
        }
        if (!power.isMod && power.power == 0)
        {
            power.power = 1;
            continue;
        }
        if (!power.isMod && power.power == 1)
        {
            power.power = value;
            continue;
        }
        if (!power.isMod)
            power.power -= 2;
        power.power = last_digit_power_mod(value, power.power);
        power.isMod = true;
    }

    value = array.back();
    array.pop_back();
    if (power.isMod)
    {
        power.power = power.power == 0 ? 3 : power.power - 1;
        return value_mod[value % 10][power.power];
    }
    else
    {
        if (power.power < 2)
            return power.power == 0 ? 1 : value % 10;

        return value_mod[value % 10][(power.power - 1) % 4];
    }
}

int main()
{
    std::cout << last_digit({0, 0, 0}) << std::endl;
    assert(last_digit({}) == 1);
    assert(last_digit({0, 0}) == 1);
    assert(last_digit({0, 0, 0}) == 0);
    assert(last_digit({1, 2}) == 1);
    assert(last_digit({3, 4, 5}) == 1);
    assert(last_digit({4, 3, 6}) == 4);
    assert(last_digit({7, 6, 21}) == 1);
    assert(last_digit({12, 30, 21}) == 6);
    assert(last_digit({2, 2, 2, 0}) == 4);
    assert(last_digit({937640, 767456, 981242}) == 0);
    assert(last_digit({123232, 694022, 140249}) == 6);
    assert(last_digit({499942, 898102, 846073}) == 6);
    assert(last_digit({1223, 4812021, 614230}) == 3);
    assert(last_digit({4626, 4812859, 332568}) == 6);
    assert(last_digit({82242, 254719, 736371}) == 8);
    assert(last_digit({83, 6}) == 9);
    assert(last_digit({0, 0, 0, 0, 0, 1, 2, 3, 3, 1, 3, 3, 2, 3, 5, 3, 3, 4, 5, 4, 3, 6, 7, 6, 1, 7, 6, 2, 7, 6, 21, 12, 30, 21, 2, 0, 1, 2, 2, 2, 0, 2, 2, 101, 2}) == 0);
    assert(last_digit({930887, 747793, 760492, 202362, 1, 1, 0, 1, 2, 0, 1, 0}) == 7);

    int rand1 = rand() % 100;
    int rand2 = rand() % 10;

    std::cout << "rand1 = " << rand1 << "\nrand2 = " << rand2 << std::endl;
    assert(last_digit({rand1}) == rand1 % 10);
}