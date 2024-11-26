/**
 * https://www.hackerrank.com/challenges/common-child/problem
 */

#include <iostream>
#include <string>
#include <string_view>
#include <vector>


/**
 * @brief Recursive Longest Common Subsequence
 *
 * @param s1 First string
 * @param m First string length
 * @param s2 Second string
 * @param n Second string length
 * @param memo Cache for memoization
 * @return The length of the longest common subsequence
 */
int r_lcs(const std::string_view s1, const int m,
          const std::string_view s2, const int n,
          std::vector<std::vector<int>> &memo)
{
    if (m == 0 || n == 0) {
        return 0;
    }

    // Cache
    if (memo[m][n] > -1) {
        return memo[m][n];
    }

    // Match
    if (s1[m - 1] == s2[n - 1]) {
        return memo[m][n] = 1 + r_lcs(s1, m - 1, s2, n - 1, memo);
    }

    // Do not match
    return memo[m][n] = std::max(r_lcs(s1, m, s2, n - 1, memo),
                                 r_lcs(s1, m - 1, s2, n, memo));
}

/**
 * @brief Tabular Longest Common Subsequence
 *
 * @param s1 First string
 * @param s2 Second string
 * @return The length of the longest common subsequence
 */
int t_lcs(const std::string_view s1, const std::string_view s2)
{
    const int m = s1.length();
    const int n = s2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

            } else {
                dp[i][j] = std::max(dp[i][j - 1],
                                    dp[i - 1][j]);
            }
        }
    }

    return dp[m][n];
}

/**
 * @param s1 First string
 * @param s2 Second string
 * @return The length of the longest common subsequence
 */
int commonChild(const std::string_view s1, const std::string_view s2)
{
    // return t_lcs(s1, s2);

    const int m = s1.length();
    const int n = s2.length();
    std::vector<std::vector<int>> memo(m + 1, std::vector<int>(n + 1, -1));

    return r_lcs(s1, m, s2, n, memo);
}


int main()
{
    const std::string s1{"SHINCHAN"};
    const std::string s2{"NOHARAAA"};

    std::cout << commonChild(s1, s2) << std::endl;  // Expected : 3

    return 0;
}
