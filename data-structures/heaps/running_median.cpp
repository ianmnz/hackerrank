/**
 * https://www.hackerrank.com/challenges/find-the-running-median/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


/**
 * @brief Computes the running median vector with O(n^2) worst-case complexity
 *
 * @param arr Array of unsorted values
 * @return Array of the running median
 */
std::vector<double> runningMedian(const std::vector<int> &arr)
{
    const int n = arr.size();

    std::vector<double> medians(n);
    std::vector<int> sorted;

    for (int i = 0; i < n; ++i) {
        const auto idx = std::upper_bound(sorted.begin(), sorted.end(), arr[i]);
        sorted.insert(idx, arr[i]);
        const int mid = (i + 1) / 2;

        if (i % 2 == 0) {
            medians[i] = (double)sorted[mid];

        } else {
            medians[i] = (sorted[mid - 1] + sorted[mid]) / 2.;
        }
    }

    return medians;
}

/**
 * @brief Computes the running median vector with O(nlogn) worst-case complexity
 *
 * @param arr Array of unsorted values
 * @return Array of the running median
 */
std::vector<double> runningMedianHeap(const std::vector<int> &arr)
{
    const int n = arr.size();

    std::vector<double> medians(n);

    // Splits the vector in two halfs:
    // Lower half for the max heap,
    // And upper half for the min heap
    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    for (int i = 0; i < n; ++i) {
        const int val = arr[i];

        if (!max_heap.empty() && val >= max_heap.top()) {
            min_heap.push(val);

        } else {
            max_heap.push(val);
        }

        // Ensures the balance between both heaps
        if (std::abs((int)(max_heap.size() - min_heap.size())) > 1) {
            if (max_heap.size() > min_heap.size()) {
                min_heap.push(std::move(max_heap.top()));
                max_heap.pop();

            } else {
                max_heap.push(std::move(min_heap.top()));
                min_heap.pop();
            }
        }

        if (i % 2 == 0) {
            medians[i] = (max_heap.size() > min_heap.size()) ? max_heap.top()
                                                             : min_heap.top();

        } else {
            medians[i] = (max_heap.top() + min_heap.top()) / 2.;
        }
    }

    return medians;
}


int main(int argc, char const *argv[])
{
    std::vector<int> arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> medians = runningMedian(arr);

    for (auto median: medians) {
        std::cout << median << " ";
    }
    std::cout << std::endl;  // Expected output: 1 1.5 2 2.5 3 3.5 4 4.5 5 5.5

    return 0;
}
