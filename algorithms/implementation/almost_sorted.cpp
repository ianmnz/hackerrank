/**
 * https://www.hackerrank.com/challenges/almost-sorted/problem
 */

#include <algorithm>
#include <iostream>
#include <vector>

/**
 * @brief Solution in O(n) but less readable
 *
 * @param arr Array of integers
 */
void almostSorted_opt(std::vector<int> &arr)
{
    const int n = arr.size();

    std::vector<int> indices;

    for (int i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) {
            indices.push_back(i - 1);
        }
    }

    // Sorted already
    if (indices.empty()) {
        std::cout << "yes" << std::endl;
        return;
    }

    auto is_sorted_after_swap = [&arr](const int l, const int r) {
        std::swap(arr[l], arr[r]);
        const bool res = std::is_sorted(arr.cbegin(), arr.cend());
        std::swap(arr[r], arr[l]);
        return res;
    };

    if (indices.size() == 1) {
        // Swap candidate is on either end of arr
        const int idx = indices[0];

        if (idx > 0 && is_sorted_after_swap(idx - 1, idx)) {
            std::cout << "yes\nswap " << idx << " " << idx + 1 << std::endl;
            return;

        } else if (idx < n - 1 && is_sorted_after_swap(idx, idx + 1)) {
            std::cout << "yes\nswap " << idx + 1 << " " << idx + 2 << std::endl;
            return;
        }
    } else if (indices.size() == 2) {
        // Swap candidates are in the interior
        const int l = indices[0];
        const int r = indices[1] + 1;

        if (is_sorted_after_swap(l, r)) {
            std::cout << "yes\nswap " << l + 1 << " " << r + 1 << std::endl;
            return;
        }
    }

    // Reverse sub array
    const int l = indices[0];
    const int r = indices.back() + 1;
    std::reverse(arr.begin() + l, arr.begin() + r + 1);
    if (std::is_sorted(arr.cbegin(), arr.cend())) {
        std::cout << "yes\nreverse " << l + 1 << " " << r + 1 << std::endl;
        return;
    }

    std::cout << "no" << std::endl;
}


/**
 * @brief Solution in O(nlogn) but more readable
 *
 * @param arr Array of integers
 */
void almostSorted(const std::vector<int> &arr)
{
    // Sorted already
    if (std::is_sorted(arr.cbegin(), arr.cend())) {
        std::cout << "yes" << std::endl;
        return;
    }

    const int n = arr.size();

    std::vector<int> indices, sorted(arr);

    // O(nlogn) : sorts the original array
    // and mark the indices where they dont match
    std::sort(sorted.begin(), sorted.end());
    for (int i = 0; i < n; ++i) {
        if (arr[i] != sorted[i]) {
            indices.push_back(i);
        }
    }

    // Checks if sequential swaps of both end of
    // the indices array would sort the original array
    // When size(indices) == 2, similar to a single swap
    // When size(indices) > 2, similar to a reverse
    for (auto left = indices.crbegin(), right = indices.crend() - 1;
         left <= right;
         ++left, --right)
    {
        if (arr[*left] != sorted[*right]) {
            std::cout << "no" << std::endl;
            return;
        }
    }

    std::cout << "yes\n"
              << (indices.size() <= 2 ? "swap " : "reverse ")
              << indices[0] + 1 << " " << indices.back() + 1 << std::endl;
}


int main()
{
    const std::vector<int> arr{1, 5, 4, 3, 2, 6};
    almostSorted(arr);  // Expected output: yes reverse 2 5
    return 0;
}
