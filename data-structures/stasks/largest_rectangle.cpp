/**
 * https://www.hackerrank.com/challenges/largest-rectangle/problem
 */

#include <iostream>
#include <vector>
#include <stack>


/**
 * @param arr: Array of heights
 * @return The max area of the façade
 */
long largestRectangle(std::vector<int>& arr)
{
    if (arr.size() == 1) {
        return arr[0];
    }

    // We add a zero to the end to compute the last area
    arr.push_back(0);
    const int n = arr.size();

    long maxarea = 0;

    std::stack<std::pair<int, int>> stk;
    stk.push(std::make_pair(0, arr[0]));

    int l_idx, height;
    for (int r_idx = 1; r_idx < n; ++r_idx) {
        l_idx = r_idx;

        // If arr[r_idx] is bigger than the previous one, we push it onto the stack
        // Otherwise we pop it from the stack until we find a smaller height
        // We compute the max area for each pop
        while (!stk.empty() && stk.top().second > arr[r_idx]) {
            l_idx = stk.top().first;
            height = stk.top().second;

            maxarea = std::max(maxarea, (long)(r_idx - l_idx) * height);

            stk.pop();
        }
        stk.push(std::make_pair(l_idx, arr[r_idx]));
    }
    return maxarea;
}


int main()
{
    std::vector<int> arr {1, 3, 5, 9, 11};

    std::cout << largestRectangle(arr) << std::endl;    // Expected output: 18

    return 0;
}
