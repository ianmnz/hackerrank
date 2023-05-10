/*
 * https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem
 */

#include <iostream>
#include <vector>

/*
 * @param ranked: Array with the current high scores in descending order
 * @param scores: Array with the sequence of scores of the player (ascending order)
 */
void climbingLeaderboard(
    const std::vector<int> ranked,
    std::vector<int>& scores)
{
    const int n = ranked.size();
    const int m = scores.size();

    // Leaderboard is dense ranked:
    //  - Highest score player is ranked 1
    //  - Players with same scores have the same ranking number
    //  - Next player(s) will be ranked with the following ranking number
    std::vector<std::pair<int, int>> learderboard(n);
    learderboard[0] = std::pair<int, int>(1, ranked[0]);

    int rank = 1;
    for (int i = 1; i < n; ++i) {
        if (learderboard[i - 1].second > ranked[i]) {
            rank++;
        }
        learderboard[i] = std::pair<int, int>(rank, ranked[i]);
    }

    std::vector<int>::iterator it = scores.begin();
    std::vector<std::pair<int, int>>::reverse_iterator rt = learderboard.rbegin();
    for (; it != scores.end();) {
        if (*it < rt->second) {
            // If the score is inferior to the current leaderboard player
            // player is ranked immediately after her
            *it = rt->first + 1;
            ++it;

        } else if (*it == rt->second) {
            // If the score is equal
            // player is ranked equally
            *it = rt->first;
            ++it;

        } else {
            // If the score is superior
            // We find the first leaderboard player with higher score
            // if there is none, player is ranked first
            if (rt != learderboard.rend()) {
                rt++;
            } else {
                *it = 1;
                ++it;
            }
        }
    }
}


int main()
{
    std::vector<int> ranked {100, 100, 50, 40, 40, 20, 10};
    std::vector<int> scores {5, 25, 50, 120};

    climbingLeaderboard(ranked, scores);

    // Expected output : 6 5 4 2 1
    for (const auto& rank : scores) {
        std::cout << rank << " ";
    }
    std::cout << "\n";

    return 0;
}
