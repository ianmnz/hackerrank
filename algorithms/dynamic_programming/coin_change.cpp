/*
 * https://www.hackerrank.com/challenges/coin-change/problem
 */

#include <iostream>
#include <vector>


/*
 * @param n: Number to be represented
 * @param coins: Available coins
 * @return Ways of representing n with coins
 */
long getWays(int n, const std::vector<int>& coins)
{
    // Initialise a vector of size n + 1 with 0's
    std::vector<long> ways(n + 1, 0);
    ways[0] = 1;

    // For each new coin we query, we add a new
    // way to count the number of ways
    for (int i = 0; i < coins.size(); ++i) {
        for (int j = coins[i]; j <= n; ++j) {
            ways[j] += ways[j - coins[i]];
        }
    }

    return ways[n];
}


int main()
{
    const int n = 3;
    const std::vector<int> coins {8, 3, 1, 2};

    std::cout << getWays(n, coins) << std::endl; // Expected output: 3

    return 0;
}
