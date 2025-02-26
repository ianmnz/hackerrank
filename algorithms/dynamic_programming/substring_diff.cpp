/**
 * https://www.hackerrank.com/challenges/substring-diff/problem
 */

#include <iostream>
#include <string_view>
#include <vector>


/**
 * @param k Threshold for differences
 * @param s1 First string
 * @param s2 Second string
 * @return THe longest common continuous substring with less than k errors
 */
int substringDiff(const int k, std::string_view s1, std::string_view s2)
{
    const int m = s1.length();
    const int n = s2.length();

    // Longest Common Substring [m + 1][n + 1] table
    std::vector<std::vector<int>> LCS(m + 1, std::vector<int>(n + 1, 0));

    int maxLCS = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {

            if (s1[i - 1] == s2[j - 1]) {
                LCS[i][j] = 1 + LCS[i - 1][j - 1];
                maxLCS = std::max(maxLCS, LCS[i][j]);
            }
        }
    }

    if (!k) {
        return maxLCS;
    }

    // 2 pointers sliding window technique
    // to find longest subarray with less zeros than k
    auto window_slide = [&LCS, k, m, n](int i, int j) {
        int lft = 0, rgt = 0;
        int ans = 0, zeros = 0;

        while ((i + rgt <= m) && (j + rgt <= n)) {
            if (!LCS[i + rgt][j + rgt]) {
                zeros++;
            }

            while (zeros > k) {
                if (!LCS[i + lft][j + lft]) {
                    zeros--;
                }
                lft++;
            }
            ans = std::max(ans, rgt - lft + 1);
            rgt++;
        }
        return ans;
    };

    int res = 0;

    // Upper Triangular Diagonals
    for (int i = 1, j = 1; j <= n; ++j) {
        res = std::max(res, window_slide(i, j));
    }

    // Lower Triangular Diagonals
    for (int j = 1, i = 2; i <= m; ++i) {
        res = std::max(res, window_slide(i, j));
    }

    return res;
}


int main()
{
    const int k = 3;
    const std::string s1 = "helloworld";
    const std::string s2 = "yellomarin";

    std::cout << substringDiff(k, s1, s2) << std::endl;  // Expected output: 8

    return 0;
}
