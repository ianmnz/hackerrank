/*
 * https://www.hackerrank.com/challenges/absolute-permutation/problem
 */

#include <iostream>
#include <vector>
#include <numeric>

/*
 * @param n: Size of the permutation with the n first natural numbers
 * @param k: Fixed absolute difference between position and value
 * @return: The smallest absolute permutation
 */
std::vector<int> absolutePermutation(const int n, const int k)
{
    std::vector<int> permutation(n, 0);

    if (k == 0) {
        std::iota(permutation.begin(), permutation.end(), 1);
        return permutation;

    }

    // The permutation only exists if n is
    // even and divisible by k, i.e., divisible
    // by 2k
    if (n % (2 * k) != 0) {
        return {-1};

    }

    for (int i = 0; i < n; ++i) {
        if (permutation[i] != 0) {
            continue;
        }

        permutation[i]     = i + k + 1;
        permutation[i + k] = i + 1;
    }

    return permutation;
}

int main()
{
    const int n = 4, k = 2;
    std::vector<int> permutation = absolutePermutation(n, k);

    // Expected output : 3 4 2 1
    for (const auto val : permutation) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}
