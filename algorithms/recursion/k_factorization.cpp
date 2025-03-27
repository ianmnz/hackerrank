/**
 * https://www.hackerrank.com/challenges/k-factorization/problem
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>


/**
 * @brief A recursive helper to factorize the objective
 *
 * @param N The objective
 * @param A Array of factors
 * @return The sequence with least states from 1 to objective
 */
std::vector<int> helper(const int N, const std::vector<int> &A)
{
    if (N == 1) {
        return {1};
    }

    for (auto a : A) {
        // Small optimization to avoid calling unnecessary divisions
        if (N < a) {
            continue;
        }

        // Small optimization to call division only once and save q, r
        const int q = N / a;
        const int r = N % a;

        if (!r) {
            if (auto res = helper(q, A); !res.empty()) {
                res.push_back(N);
                return res;
            }
        }
    }

    return {};
}


/**
 * @param N The objective
 * @param A Array of factors
 * @return The sequence with least states from 1 to objective
 */
std::vector<int> kFactorization(const int N, std::vector<int> &A)
{
    std::sort(A.begin(), A.end(), std::greater<>());

    const std::vector<int> res = helper(N, A);
    if (res.empty()) {
        return {-1};
    }
    return res;
}


int main()
{
    const int N = 72;
    std::vector<int> A{2, 4, 6, 9, 3, 7, 16, 10, 5};
    const auto states = kFactorization(N, A);

    // Expected output: 1 2 8 72
    for (const auto state : states) {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    return 0;
}
