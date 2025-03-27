/**
 * https://www.hackerrank.com/challenges/aorb/problem
 */

#include <iostream>
#include <string_view>
#include <unordered_map>
#include <vector>


/**
 * @param tickets Array of strings of tickets numbers
 * @return The number of pairs of winning tickets
 */
long winningLotteryTicket(const std::vector<std::string> &tickets)
{
    std::unordered_map<int, long> bitmasks;

    for (std::string_view ticket : tickets) {
        // For each char present in the string
        // we mark it as 1 in the bitmask
        // and increment its frequency
        int mask = 0b00'0000'0000;
        for (const char c : ticket) {
            mask |= 1 << (int)(c - '0');
        }
        bitmasks[mask]++;
    }

    long winning_pairs = 0l;

    for (auto it1 = bitmasks.cbegin(); it1 != bitmasks.cend(); ++it1) {
        const auto &[mask1, freq1] = *it1;

        if (mask1 == 0b11'1111'1111) {
            // If mask1 is already full of 1's
            // we count all possible pairs
            // n choose 2
            winning_pairs += (freq1 * (freq1 - 1)) / 2l;
        }
        for (auto it2 = std::next(it1); it2 != bitmasks.cend(); ++it2) {
            const auto &[mask2, freq2] = *it2;

            if ((mask1 | mask2) == 0b11'1111'1111) {
                // If OR-ing both masks is full of 1's
                // we count all possible permutations
                // n * m
                winning_pairs += freq1 * freq2;
            }
        }
    }

    return winning_pairs;
}


int main()
{
    std::vector<std::string> tickets{"129300455", "5559948277", "012334556",
                                     "56789", "123456879"};
    std::cout << winningLotteryTicket(tickets)
              << std::endl;  // Expected output: 5
    return 0;
}
