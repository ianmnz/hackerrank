/**
 * https://www.hackerrank.com/challenges/kindergarten-adventures/problem
 */

#include <iostream>
#include <vector>
#include <limits>


/**
 * @param needed: Array of needed extra time
 * @return The optimum position to start
 */
int solve(const std::vector<int>& needed)
{
    const int n = needed.size();
    int* finished = new int[n];

    for (int i = 0; i < n; ++i) {
        finished[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        // needed[i] = 0 means the student will always finish
        // and needed[i] = n means she will never finish
        // In that case, we can ignore both
        if (needed[i] != 0 && needed[i] != n) {
            // The student finishes when starting from any position in
            // [i + 1, n - (needed[i] - i)]
            // (we wrap around with %n)
            finished[(i + 1) % n]++;
            finished[(n - (needed[i] - i) + 1) % n]--;
        }
    }

    int start = 1;
    long count = 0, max_count = std::numeric_limits<long>::min();
    for (int i = 0; i < n; ++i) {
        count += finished[i];

        if (count > max_count) {
            max_count = count;
            start = i + 1;
        }
    }

    delete[] finished;

    return start;
}


int main()
{
    const std::vector<int> needed = {1, 0, 0};
    std::cout << solve(needed) << std::endl;    // Expected output: 2
    return 0;
}
