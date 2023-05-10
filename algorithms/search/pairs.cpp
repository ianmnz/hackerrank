/**
 * https://www.hackerrank.com/challenges/pairs/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>


int pairs(const int k, std::vector<int>& arr)
{
    const int n = arr.size();
    int nb_pairs = 0;

    // We sort the vector forcing all diferences to be sequential
    std::sort(arr.begin(), arr.end());

    for (int i = 0; i < n - 1; ++i) {
        // We check for each value if the there is
        // another value with difference K
        // We use a binary search since the vector is sorted
        if (std::binary_search(arr.begin() + (i + 1), arr.end(), arr[i] + k)) {
            nb_pairs++;
        }
    }

    return nb_pairs;
}


int main()
{
    const int k = 2;
    std::vector<int> arr {1, 5, 3, 4, 2};

    std::cout << pairs(k, arr) << std::endl;    // Expected output: 3
    return 0;
}
