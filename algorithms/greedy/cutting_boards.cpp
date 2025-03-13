/**
 * https://www.hackerrank.com/challenges/board-cutting/problem
 */

#include <algorithm>
#include <iostream>
#include <vector>


/**
 * @param cost_h Array of horizontal cut costs
 * @param cost_v Array of vertical cut costs
 * @return The minimal cost of cutting the board in 1x1 squares
 */
int boardCutting(std::vector<int> &cost_h, std::vector<int> &cost_v)
{
    constexpr int mod = 1'000'000'007;
    const int m = cost_h.size();  // horizontal cuts
    const int n = cost_v.size();  // vertical cuts

    // Sort cuts in descending order of costs
    std::sort(cost_h.begin(), cost_h.end(), std::greater<>());
    std::sort(cost_v.begin(), cost_v.end(), std::greater<>());

    // Using long here to avoid int overflow when multiplying below
    long cost = 0;
    int v_segments = 1, h_segments = 1;

    int i = 0, j = 0;
    while (i < m && j < n) {
        // While there are cuts available in both directions
        // choose the more expensive one
        if (cost_h[i] >= cost_v[j]) {
            cost += (long)v_segments * cost_h[i++];
            h_segments++;

        } else {
            cost += (long)h_segments * cost_v[j++];
            v_segments++;
        }
        cost %= mod;
    }

    while (i < m) {
        // While there are any remaining horizontal cut
        cost += (long)v_segments * cost_h[i++];
        h_segments++;
        cost %= mod;
    }

    while (j < n) {
        // While there are any remaining vertical cut
        cost += (long)h_segments * cost_v[j++];
        v_segments++;
        cost %= mod;
    }

    return cost;
}


int main()
{
    std::vector<int> cost_h {2, 1, 3, 1, 4};
    std::vector<int> cost_v {4, 1, 2};
    std::cout << boardCutting(cost_h, cost_v) << std::endl;  // Expected output: 42
    return 0;
}
