/*
 * https://www.hackerrank.com/challenges/equal/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>


/*
 * @param arr: Array with initial distribution
 * @return The number of operations to equalize
 */
int equal(const std::vector<int>& arr)
{
    int nb_op_0 = 0;    // Canonical number of operations
    int nb_op_1 = 0;    // If we add +1 to all but one in a strategic manner
    int nb_op_2 = 0;    // If we add +2 to all but one in a strategic manner
    const int base = *std::min_element(arr.begin(), arr.end());

    for (int delta : arr) {
        delta -= base;

        // Quotients and remainders
        const int q0 = delta/5, r0 = delta%5;
        const int q1 = q0 + (r0 + 1)/5, r1 = (r0 + 1)%5; // delta+1
        const int q2 = q0 + (r0 + 2)/5, r2 = (r0 + 2)%5; // delta+2

        // qi = number of 5's
        // ri/2 = number of 2's
        // ri%2 = number of 1's
        nb_op_0 += q0 + r0/2 + r0%2;
        nb_op_1 += q1 + r1/2 + r1%2;
        nb_op_2 += q2 + r2/2 + r2%2;
    }

    return std::min(nb_op_0, std::min(nb_op_1, nb_op_2));
}


int main()
{
    const std::vector<int> arr {10, 7, 12};
    std::cout << equal(arr) << std::endl; // Expected output: 3

    return 0;
}
