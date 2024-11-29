/**
 * https://www.hackerrank.com/challenges/sherlock-and-anagrams/problem
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>


/**
 * @param s String to look for anagrams in substrings
 * @return the number of anagrams
 */
int sherlockAndAnagrams(const std::string &s)
{
    const int n = s.length();
    std::unordered_map<std::string, int> look_up_table;

    for (int i = 0; i < n; ++i) {
        for (int l = 1; l <= (n - i); ++l) {
            std::string substr = s.substr(i, l);
            std::sort(substr.begin(), substr.end());

            look_up_table[substr]++;
        }
    }

    int count = 0;
    for (const auto &[_, val] : look_up_table) {
        if (val >= 2) {
            count += val * (val - 1) / 2;
        }
    }
    return count;
}


int main()
{
    const std::string s{"abba"};

    std::cout << sherlockAndAnagrams(s) << std::endl;  // Expected : 4

    return 0;
}
