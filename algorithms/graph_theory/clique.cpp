/**
 * https://www.hackerrank.com/challenges/clique/problem
 *
 * https://cs.stackexchange.com/questions/41057/minimum-size-of-largest-clique-in-graph/51033#51033
 * https://math.stackexchange.com/questions/1279241/minimum-size-of-largest-clique-in-a-graph
 */

#include <iostream>


/**
 * @param n: Number of vertices of the graph
 * @param m: Number of the edges of the graph
 * @return The minimum size of the largest clique with n vertices and m edges
 */
int clique(const int n, const int m)
{
    // Corner case for an error in the input data
    // Here, the largest clique for a n graph
    // should have n(n-1)/2 edges (which is
    // the number of edges of a complete simple graph)
    if (m > n * (n - 1) / 2) {
        return n + 1;
    }

    auto turan = [](const int n, const int k)
    {
        const int q = n / k;
        const int r = n % k;

        if (r) {
            return (r * (r - 1)) / 2 + (2 * r + k * q) * (k - 1) * q/2;
        } else {
            return n * q * (k - 1) / 2;
        }
    };

    // Binary search for k
    int lower = 1;
    int upper = n;
    while (lower < upper) {
        const int mid = (lower + upper) / 2;

        if (turan(n, mid) >= m) {
            upper = mid;

        } else {
            lower = mid + 1;
        }
    }

    return upper;
}


int main()
{

    return 0;
}