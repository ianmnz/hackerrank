/**
 * https://www.hackerrank.com/challenges/game-of-two-stacks/problem
 */

#include <iostream>
#include <vector>


/**
 * @param maxSum Max combined sum of both stacks
 * @param a First stack
 * @param b Second stack
 * @return The max number of popping moves
 */
int twoStacks(const int maxSum, const std::vector<int>& a, const std::vector<int>& b)
{
    const int n = a.size();
    const int m = b.size();

    int idx_a = 0, idx_b = 0;
    int running_sum = 0, nb_moves = 0;

    // We pop all elements from first stack while the maxSum is not reached
    while (idx_a < n && (running_sum + a[idx_a] <= maxSum)) {
        running_sum += a[idx_a++];
        ++nb_moves;
    }

    // Then, when we pop the elements of the second stack
    while (idx_b < m && 0 <= idx_a) {
        running_sum += b[idx_b++];

        // If the maxSum is reached, we remove the last element of the first stack
        while (0 < idx_a && running_sum > maxSum) {
            running_sum -= a[--idx_a];
        }

        // Doing so, the nb_moves will never decrease and will increase if either:
        // 1) we can pop elements from the second stack without removing elements from the first
        // 2) removing an element from the first allows for popping 2 or more elements from the second
        if (running_sum <= maxSum && (nb_moves < idx_a + idx_b)) {
            nb_moves = idx_a + idx_b;
        }
    }

    return nb_moves;
}


int main()
{
    const int maxSum = 10;
    const std::vector<int> a {4, 2, 4, 6, 1};
    const std::vector<int> b {2, 1, 8, 5};

    std::cout << twoStacks(maxSum, a, b) << std::endl;  // Expected output: 4

    return 0;
}
