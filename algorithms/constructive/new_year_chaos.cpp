/**
 * https://www.hackerrank.com/challenges/new-year-chaos/problem
 */

#include <iostream>
#include <vector>


/**
 * @param arr: Array of unsorted numbers
 */
void minimumBribes(std::vector<int>& arr)
{
    const int n = arr.size();

    int swaps = 0;
    int start = 0;
    bool sorted = false;

    while (!sorted) {
        // We assume sorted until we find a misplaced value
        sorted = true;

        for (int i = start; i < n - 1; ++i) {
            // If distance to the right position is superior to 2
            // it means the value (i + 1) made more than 2 swaps
            if (arr[i] - i > 3) {
                std::cout << "Too chaotic" << std::endl;
                return;
            }

            // Once the vector is sorted, there's no need to look it again
            // So on the next for-loop we start from the last sorted position
            if (sorted && (arr[i] == i + 1)) {
                start = i + 1;
                continue;
            }

            sorted = false;

            // If it's not sorted up to here, it means
            // either left < right: we do nothing
            // or right > left: we need to swap them
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                ++swaps;
                break;
            }
        }
    }

    std::cout << swaps << std::endl;
}


int main()
{
    std::vector<int> arr {1, 2, 5, 3, 7, 8, 6, 4};

    minimumBribes(arr); // Expected output: 7

    return 0;
}
