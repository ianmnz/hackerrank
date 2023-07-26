/**
 * https://www.hackerrank.com/challenges/jim-and-the-skyscrapers/problem
 */

#include <iostream>
#include <vector>
#include <stack>


/**
 * @param arr : Array of heights
 * @return The number of routes possibles
 */
long solve(const std::vector<int>& arr)
{
    const int n = arr.size();

    // Height and frequency stack
    // We stack pairs monotonically (decreasing) by height
    std::stack<std::pair<int, int>> stk;

    long routes = 0l;
    for (int i = 0; i < n; ++i) {
        const int h = arr[i];

        while (!stk.empty() && h > stk.top().first) {
            stk.pop();
        }

        if (!stk.empty() && h == stk.top().first) {
            // We increment the number of routes
            // and then increment the frequency
            routes += stk.top().second++;

        } else {
            stk.push(std::make_pair(h, 1));
        }
    }

    // We count both directions of the routes
    return 2l * routes;
}


int main()
{
    const std::vector<int> arr {3, 2, 1, 2, 3, 3};

    std::cout << solve(arr) << std::endl;   // Expected output: 8

    return 0;
}
