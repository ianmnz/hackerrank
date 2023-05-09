/*
 * https://www.hackerrank.com/challenges/candies/problem
 */

#include <iostream>
#include <vector>
#include <numeric>


long candies(const int n, const std::vector<int>& arr)
{
    std::vector<long> candies(n, 1l);

    // We do a first pass left-to-right
    // to give the student to the right
    // more candies if its grade is superior
    for (int i = 1; i < n; ++i) {
        const int prev = arr[i - 1];
        const int curr = arr[i];
        if (curr > prev) {
            candies[i] = candies[i - 1] + 1l;
        }
    }

    // Then we do a second pass right-to-left
    // to assure that the student to the left
    // gets more candies if its grade is superior
    for (int j = n - 2; j >= 0; --j) {
        const int prev = arr[j + 1];
        const int curr = arr[j];
        if (curr > prev) {
            candies[j] = std::max(candies[j], candies[j + 1] + 1l);
        }
    }

    // The then sum the number of candies needed
    return std::accumulate(candies.begin(), candies.end(), 0l);
}


int main()
{
    const int n = 6;
    std::vector<int> arr {4, 6, 4, 5, 6, 2};

    std::cout << candies(n, arr) << std::endl; // Expected output: 10

    return 0;
}
