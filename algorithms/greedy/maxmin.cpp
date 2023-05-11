/*
 * https://www.hackerrank.com/challenges/angry-children/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>


/*
 * @param k: Distance between elements of the array
 * @param arr: Base array
 * @return Unfairness value
 */
int maxMin(const int k, std::vector<int> arr)
{
    std::sort(arr.begin(), arr.end());

    int unfairness = arr[k-1] - arr[0];

    for (int i = k; i < arr.size(); ++i) {
        const int aux = arr[i] - arr[i - k + 1];

        if (aux < unfairness) {
            unfairness = aux;
        }
    }

    return unfairness;
}


int main()
{
    const int k = 3;
    const std::vector<int> arr {10, 100, 300, 200, 1000, 20, 30};

    std::cout << maxMin(k, arr) << std::endl; // Expected output: 20

    return 0;
}
