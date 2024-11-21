/**
 * https://www.hackerrank.com/challenges/stone-division-2/problem
 */

#include <iostream>
#include <vector>
#include <map>


/**
 * @param n Pile height
 * @param S Set of m distinct integers
 * @param cache Map for caching
 * @return Max number of moves
 */
long stoneDivision(const long n, const std::vector<long>& S, std::map<long, long>& cache)
{

    if (auto found = cache.find(n);
        found != cache.end())
    {
        return found->second;
    }

    long nb_moves = 0l;

    for (const auto& x : S) {
        const long q = n / x;
        const long r = n % x;

        if (r != 0 || q == 1l) {
            continue;
        }

        nb_moves = std::max(nb_moves, 1 + q * stoneDivision(x, S, cache));
    }

    cache[n] = nb_moves;
    return nb_moves;
}


int main()
{
    const long n = 12;
    const std::vector<long> S {2l, 4l, 3l};
    std::map<long, long> cache {};

    std::cout << stoneDivision(n, S, cache) << std::endl;  // Expected: 4

    return 0;
}
