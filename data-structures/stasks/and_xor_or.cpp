/**
 * https://www.hackerrank.com/challenges/and-xor-or/problem
 */

#include <iostream>
#include <stack>
#include <vector>


/**
 * @param arr Array of integers
 * @return the maximum of Si
 */
int andXorOr(const std::vector<int> &arr)
{
    int maximum = 0;
    std::stack<int> stk;

    for (const int a : arr) {
        while (!stk.empty() && a <= stk.top()) {
            maximum = std::max(maximum, a ^ stk.top());
            stk.pop();
        }

        if (!stk.empty()) {
            maximum = std::max(maximum, a ^ stk.top());
        }
        stk.push(a);
    }

    return maximum;
}


int main()
{
    const std::vector<int> arr{9, 6, 3, 5, 2};
    std::cout << andXorOr(arr) << std::endl;  // Expected output: 15
    return 0;
}
