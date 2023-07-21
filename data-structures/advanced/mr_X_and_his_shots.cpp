/**
 * https://www.hackerrank.com/challenges/x-and-his-shots/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>


/**
 * @param shots Array with shots' intervals
 * @param players Array with players' intervals
 * @return The number of intersections
 */
int solve(const std::vector<std::vector<int>>& shots, const std::vector<std::vector<int>>& players)
{
    const int n = shots.size();
    const int m = players.size();

    std::vector<int> lefts; lefts.reserve(n);
    std::vector<int> rights; rights.reserve(n);

    // We store left and right sides of the shot's interval
    // in their own vectors
    for (const auto& shot : shots) {
        lefts.push_back(shot[0]);
        rights.push_back(shot[1]);
    }

    // We sort them to use binary searches
    std::sort(lefts.begin(), lefts.end());
    std::sort(rights.begin(), rights.end());

    // If all players were able to stop all shots,
    // the total would be n * m
    long total = (long) n * m;

    // We will decrease this value every time a shot interval
    // and a player interval don't intersect
    // Two intervals [a, b] and [c, d] don't intersect if
    // (b < c) or (a > d)
    for (const auto& player : players) {
        total -= (long)(lefts.end() - std::upper_bound(lefts.begin(), lefts.end(), player[1]));
        total -= (long)(std::upper_bound(rights.begin(), rights.end(), player[0] - 1) - rights.begin());
    }

    return (int)total;
}


int main()
{
    const std::vector<std::vector<int>> shots {{1, 2}, {2, 3}, {4, 5}, {6, 7}};
    const std::vector<std::vector<int>> players {{1, 5}, {2, 3}, {4, 7}, {5, 7}};

    std::cout << solve(shots, players) << std::endl;    // Expected output: 9

    return 0;
}
