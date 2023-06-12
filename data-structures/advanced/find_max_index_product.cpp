/**
 * https://www.hackerrank.com/challenges/find-maximum-index-product/problem
 */

#include <iostream>
#include <vector>
#include <stack>


/**
 * Naive solution
 * @param arr: Array of values
 * @return The maximum index product
 */
long solve(const std::vector<int>& arr)
{
    const int n = arr.size();
    long maxIndexProd = 0;

    for (int i = 1; i < n - 1; ++i) {

        // If they are adjancent, they will have the same index
        // so no need to recalculate
        if (i > 1 && arr[i] == arr[i - 1]) {
            continue;
        }

        int left = 0;
        for (int j = i - 1; j >= 0; --j) {
            if (arr[j] > arr[i]) {
                left = j + 1;
                break;
            }
        }

        // If left == 0, no need to look for the right
        if (!left) {
            continue;
        }

        int right = 0;
        for (int k = i + 1; k < n; ++k) {
            if (arr[k] > arr[i]) {
                right = k + 1;
                break;
            }
        }

        // If right == 0, no need to compute index
        if (!right) {
            continue;
        }

        maxIndexProd = std::max(maxIndexProd, (long) left * right);
    }

    return maxIndexProd;
}


/**
 * Solution using stacks
 * @param arr: Array of values
 * @return The maximum index product
 */
long solve(const std::vector<int>& arr)
{
    const int n = arr.size();
    std::vector<int> left(n, 0), right(n, 0);

    std::stack<int> lstack, rstack;

    for (int i = 0; i < n; ++i) {
        while(!lstack.empty() && arr[lstack.top()] <= arr[i]) {
            lstack.pop();
        }
        if (!lstack.empty()) {
            left[i] = lstack.top() + 1;
        }
        lstack.push(i);
    }

    for (int i = n - 1; i >= 0; --i) {
        while(!rstack.empty() && arr[rstack.top()] <= arr[i]) {
            rstack.pop();
        }
        if (!rstack.empty()) {
            right[i] = rstack.top() + 1;
        }
        rstack.push(i);
    }

    long maxIndexProd = 0;
    for (int i = 1; i < n - 1; ++i) {
        maxIndexProd = std::max(maxIndexProd, (long) left[i] * right[i]);
    }

    return maxIndexProd;
}


int main()
{
    const std::vector<int> arr {5, 4, 3, 4, 5};

    std::cout << solve(arr) << std::endl;   // Expected output: 8

    return 0;
}
