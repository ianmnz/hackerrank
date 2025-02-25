/**
 * https://www.hackerrank.com/challenges/knightl-on-chessboard/problem
 */

#include <iostream>
#include <vector>


/**
 * @param prices Array of daily prices
 * @return The max profit of trading on given prices
 */
long stockMax(const std::vector<int> &prices)
{
    long profit = 0l;
    int max_price = 0;

    for (int i = prices.size() - 1; i >= 0; --i) {
        max_price = std::max(max_price, prices[i]);
        profit += (long)std::max(0, max_price - prices[i]);
    }

    return profit;
}


int main()
{
    const std::vector<int> prices {1, 3, 1, 2};
    std::cout << stockMax(prices) << std::endl; // Expected output: 3
    return 0;
}
