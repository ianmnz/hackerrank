/*
 * https://www.hackerrank.com/challenges/maxsubarray/problem
 */

#include <iostream>
#include <vector>


/*
 * Kadane's Algorithm
 * @param arr: Array of numbers
 * @return MaxSubarray and MaxSequence
 */
std::vector<long> maxSubarray(const std::vector<int>& arr)
{
    long subarr = 0l;
    long subseq = 0l;
    long max_subarr = std::numeric_limits<long>::min();
    long max_arr_j = std::numeric_limits<long>::min();

    for (const long arr_j : arr) {
        // We keep track of the best subarray up to j
        subarr = std::max(arr_j, subarr + arr_j);
        max_subarr = std::max(subarr, max_subarr);

        // For the subsequence, we keep only positive values of arr
        // If they are all negatives, we keep only the largest
        subseq += std::max(0l, arr_j);
        max_arr_j = std::max(max_arr_j, arr_j);
    }

    return {max_subarr, (subseq > 0l? subseq : max_arr_j)};
}


int main()
{
    std::vector<int> arr {-1, 2, 3, -4, 5, 10};

    std::vector<long> output = maxSubarray(arr);
    std::cout << output[0] << ", " << output[1] << std::endl; // Expected output: 16, 20

    return 0;
}
