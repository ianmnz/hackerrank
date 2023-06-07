/**
 * https://www.hackerrank.com/challenges/larrys-array/problem
 */

#include <iostream>
#include <vector>


/**
 * @param arr: Array of unsorted numbers
 * @return True if arr is sortable, false otherwise
 */
bool larrysArray(const std::vector<int>& arr)
{
    const int n = arr.size();

    // If the number of inversions is odd,
    // the arr is unsortable since each rotation
    // either creates the number of inversions by 2 or 0:
    // [2, 3, 4] -> [3, 4, 2] -> [4, 2, 3] -> [2, 3, 4]
    //     0            2            2            0
    bool isNbInversionsEven = true;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                isNbInversionsEven = !isNbInversionsEven;
            }
        }
    }
    return isNbInversionsEven;
}


int main()
{
    const std::vector<int> arr {1, 6, 5, 2, 4, 3};

    std::cout << std::boolalpha << larrysArray(arr) << std::endl; // Expected output: true

    return 0;
}
