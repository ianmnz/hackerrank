/**
 * https://www.hackerrank.com/challenges/gridland-metro/problem
 */

#include <array>
#include <iostream>
#include <set>
#include <utility>
#include <vector>


/**
 * @param n Nb of rows
 * @param m Nb of columns
 * @param k Nb of tracks
 * @param tracks Array of tracks
 * @return Nb of available places in the grid
 */
long gridlandMetro(const long n,
                   const long m,
                   const int k,
                   std::vector<std::array<int, 3>>& tracks)
{
    using Interval = std::pair<long, long>;
    std::set<Interval> intervals;
    
    for (const auto& [r, c1, c2] : tracks) {
        const long aux = (long)(r - 1) * m;
        intervals.emplace((long)(c1 - 1) + aux, (long)(c2 - 1) + aux);
    }
    
    long available = 0l;
    long it = 0l;

    for (const auto& interval : intervals) {
        if (it < interval.first) {
            available += interval.first - it;
            it = interval.second + 1l;

        } else if (it <= interval.second) {
            it = interval.second + 1l;
        }
    }
    
    if (const long total = m * n; it < total) {
        available += total - it;
    }
    
    return available;
}


int main()
{
    const long n = 4;
    const long m = 4;
    const int  k = 3;
    std::vector<std::array<int, 3>> tracks {{2, 2, 3}, {3, 1, 4}, {4, 4, 4}};
    std::cout << gridlandMetro(n, m, k, tracks) << std::endl;    // Expected output: 9

    return 0;
}
