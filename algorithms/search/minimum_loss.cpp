/*
 * https://www.hackerrank.com/challenges/minimum-loss/problem
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>


/*
 * @param prices: Prices of houses
 * @return The minimum loss
 */
long minimumLoss(const std::vector<long>& prices)
{
    const int n = prices.size();
    long min_loss = std::numeric_limits<long>::max();

    // We create a vector sorted by prices that
    // keeps the information of the years
    std::vector<std::tuple<int, long>> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = std::make_tuple(i, prices[i]);
    }

    std::sort(data.begin(), data.end(),
              [](const std::tuple<int, long>& lhs, const std::tuple<int, long>& rhs)
              {
                return std::get<1>(lhs) < std::get<1>(rhs);
              }
             );

    // We then do a linear search with buying and selling prices
    // by only looking neighbour prices
    for (int i = 0; i < n - 1; ++i) {
        const int sell_idx = std::get<0>(data[i]);
        const long sell_prc = std::get<1>(data[i]);

        const int buy_idx = std::get<0>(data[i + 1]);
        const long buy_prc = std::get<1>(data[i + 1]);

        // We check that the buying year is previous to the selling year
        if (sell_idx < buy_idx) {
            continue;
        }

        // We are only looking for losses
        if (sell_prc > buy_prc) {
            continue;
        }

        const long loss = buy_prc - sell_prc;

        if (loss < min_loss) {
            min_loss = loss;
        }
    }
    return min_loss;
}


int main()
{
    const std::vector<long> prices {20, 7, 8, 2, 5};

    std::cout << minimumLoss(prices) << std::endl;  // Expected output: 2

    return 0;
}
