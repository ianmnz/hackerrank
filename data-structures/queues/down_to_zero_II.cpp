/**
 * https://www.hackerrank.com/challenges/down-to-zero-ii/problem
*/

#include <iostream>


/**
 * Pre-computes the results up to N
 * @param N The maximum possible value
 * @param dp Array to be filled
 */
void precompute(const int N, int* dp)
{
    std::fill(dp, dp + N, -1);
    dp[0] = 0;

    for (int i = 1; i < N; ++i) {
        if (dp[i] < 0 || dp[i] > (dp[i - 1] + 1)) {
            dp[i] = dp[i - 1] + 1;
        }

        for (int j = 1; j <= i && j * i < N; ++j) {
            if (dp[j * i] < 0 || (dp[i] + 1 < dp[j * i])) {
                dp[j * i] = dp[i] + 1;
            }
        }
    }
}

/**
 * Queries the table for the value of n
 * @param n The value to be queried
 * @param dp The pre-filled array
 * @return The minimum number of moves to reduce n to 0
 */
int downToZero(const int n, const int* dp)
{
    return dp[n];
}


int main()
{
    const int N = 1001;
    int* dp = new int[N];

    precompute(N, dp);

    const int n = 4;
    std::cout << downToZero(n, dp) << std::endl;    // Expected output: 3

    delete[] dp;

    return 0;
}
