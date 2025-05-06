/**
 * https://www.hackerrank.com/challenges/short-palindrome/problem
 */

#include <array>
#include <iostream>
#include <string_view>

/**
 * @param s String to search for palindromic 4-tuples such that (x, y, y, x)
 * @return The nb of palindromic 4-tuples
 */
int shortPalindrome(std::string_view s)
{
    constexpr int mod = 1'000'000'007;
    constexpr int N = 26;

    long res = 0l;

    // Stores the nb of times a pattern has been seen so far
    std::array<int, N> singles{};    // char x
    std::array<int, N * N> pairs{};  // pair (x,y)
    std::array<int, N> triplets{};   // triplet (x, y, y)

    for (const char c : s) {
        const int j = c - 'a';
        res = (res + triplets[j]) % mod;

        for (int i = 0; i < N; ++i) {
            const int ij = j + N * i;
            triplets[i] = (triplets[i] + pairs[ij]) % mod;
            pairs[ij] = (pairs[ij] + singles[i]) % mod;
        }
        singles[j]++;
    }
    return res;
}

int main()
{
    const std::string s = "abbaab";
    std::cout << shortPalindrome(s) << std::endl;  // Expected output: 4

    return 0;
}
