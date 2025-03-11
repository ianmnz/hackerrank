/**
 * https://www.hackerrank.com/challenges/crush/problem
 */

#include <array>
#include <iostream>
#include <vector>


/**
 * @param n The size of the array
 * @param queries An array of [lft, rgt, k] queries
 * @return The maximum value of the array
 */
long arrayManipulation(const int n,
                       const std::vector<std::array<int, 3>> &queries)
{
    std::vector<long> arr(n, 0);

    // Mark the k value jump for each interval [lft - 1, rgt):
    // We increase on entry (left)
    // and decrease on exit (right)
    for (auto &[lft, rgt, k] : queries) {
        arr[lft - 1] += k;
        if (rgt < n)
            arr[rgt] -= k;
    }

    // Compute prefix sum and track the maximum value
    long max_sum = 0l;
    long curr_sum = 0l;
    for (auto val : arr) {
        curr_sum += val;
        max_sum = std::max(max_sum, curr_sum);
    }
    return max_sum;
}


/**
 * @brief Same as before, but with O(m*log m) complexity and O(m) space
 *
 * @param n The size of the array
 * @param queries An array of [lft, rgt, k] queries
 * @return The maximum value of the array
 */
long arrayManipulation_opt(const int n,
                           const std::vector<std::array<int, 3>> &queries)
{
    // Instead of using O(n) space to stock all jumps
    // just keep track of each jump in 2 pairs
    std::vector<std::pair<int, int>> jumps;

    // Mark values jumps for each interval [lft, rgt)
    // where we increase by k on entry (left)
    // and decrease by k on exit (right)
    for (auto &[lft, rgt, k] : queries) {
        jumps.push_back(std::make_pair(lft - 1, k));
        jumps.push_back(std::make_pair(rgt, -k));
    }

    // Uses O(m * log m) complexity to sort vector
    std::sort(jumps.begin(), jumps.end());

    // Compute prefix sum and track the maximum value
    long max_sum = 0l;
    long curr_sum = 0l;
    for (auto jump : jumps) {
        curr_sum += jump.second;
        max_sum = std::max(max_sum, curr_sum);
    }
    return max_sum;
}


int main()
{
    const int n = 5;
    const std::vector<std::array<int, 3>> queries{
        {1, 2, 100}, {2, 5, 100}, {3, 4, 100}};

    std::cout << arrayManipulation(n, queries)
              << std::endl;  // Expected output: 200

    return 0;
}
