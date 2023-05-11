/*
 * https://www.hackerrank.com/challenges/greedy-florist/problem
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>


/*
 * @param k: Number of buyers
 * @param flowers: Cost of the flowers
 * @return Total cost
 */
long getMinimumCost(const int k, const std::vector<int> flowers)
{
    const int n = flowers.size();

    // Corner case : If less flowers than buyers
    if (n <= k) {
        return std::accumulate(flowers.begin(), flowers.end(), 0l);
    }

    // We will sort the flowers in descending order
    std::sort(flowers.begin(), flowers.end(), std::greater<int>());

    long multiplier = 0l;
    long cost = 0l;

    // And for each cycle of friends, we add 1 to the multiplier
    for (int i = 0; i < n; ++i) {
        if (i % k == 0) {
            multiplier++;
        }
        cost += flowers[i] * multiplier;
    }

    return cost;
}

int main()
{
    const int k = 3;
    const std::vector<int> flowers {1, 2, 3, 4};

    std::cout << getMinimumCost(k, flowers) << std::endl; // Expected output: 11

    return 0;
}
