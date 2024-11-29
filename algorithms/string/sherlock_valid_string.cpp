/**
 * https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
 */

#include <iostream>
#include <string>
#include <unordered_map>


/**
 * @param s String to be checked for validity
 * @return true if is valid,
 * @return false otherwise
 */
bool isValid(const std::string &s)
{
    std::array<int, 26> freqs{};
    std::unordered_map<int, int> counter;

    for (const auto c : s) {
        freqs[(int)(c - 'a')]++;
    }

    for (const auto freq : freqs) {
        if (freq > 0) {
            counter[freq]++;
        }
    }

    if (counter.size() == 1) {
        return true;
    }

    if (counter.size() > 2) {
        return false;
    }

    // Only two frequencies
    const auto [freq1, count1] = *counter.begin();
    const auto [freq2, count2] = *std::next(counter.begin());

    // Either count1 or count2 must be 1
    if (count1 == 1) {
        if (freq1 == 1 || freq1 == freq2 + 1)
            return true;

    } else if (count2 == 1) {
        if (freq2 == 1 || freq2 == freq1 + 1)
            return true;
    }

    return false;
}


int main()
{
    const std::string s{"aaaaabbcc"};

    std::cout << std::boolalpha << isValid(s) << std::endl;  // Expected : false

    return 0;
}
