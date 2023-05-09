/*
 * https://www.hackerrank.com/challenges/sherlock-and-cost/problem
 */

#include <iostream>
#include <vector>


int cost(const std::vector<int>& B)
{
    const int n = B.size();

    // The optimum should be zig-zagging between
    // the vector B and 1
    int cost_b = 0;
    int cost_1 = 0;

    for (int i = 1; i < n; ++i) {
        const int from_b_to_b = std::abs(B[i] - B[i - 1]);  // We either keep on B's between indexes
        const int from_1_to_b = std::abs(B[i] - 1);         // Or switch from 1 to B
        const int from_b_to_1 = std::abs(1 - B[i - 1]);     // Or switch from B to 1
        // const int from_1_to_1 = std::abs(1 - 1); = 0     // Or keep on 1's

        const int aux = std::max(cost_b + from_b_to_b, cost_1 + from_1_to_b);
        cost_1 = std::max(cost_1, cost_b + from_b_to_1);    // We either finish on 1
        cost_b = aux;                                       // Or finish on B
    }

    return std::max(cost_b, cost_1);
}


int main()
{
    const std::vector<int> arr {10, 1, 10, 1, 10};

    std::cout << cost(arr) << std::endl; // Expected output: 36

    return 0;
}
