/*
 * https://www.hackerrank.com/challenges/queens-attack-2/problem
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using pq_t = std::priority_queue<int, std::vector<int>, std::greater<int>>;

struct Square
{
    int r;
    int c;
};

/*
 * @param n: board side's length (index starts with 1)
 * @param k: number of obstacles
 * @param queen: queen's square position
 * @param obstacles: array of k obstacles, with each i-th obstacle square position
 * @return: number of availables squares the queen can attack
 */
int queensAttack(int n, int k, const Square queen, std::vector<Square> obstacles)
{
    pq_t upp, dwn, lft, rgt;
    pq_t upl, upr, dwl, dwr;

    // We will find every obstacle in one of the 8 directions
    // the queen can move from it's point :
    // Up, Down, Left, Right, Up-Left, Up-Right, Down-Left, Down-Right
    // We will stock them in priority queues so the closer obstacle
    // will be on the top
    for (int i = 0; i < k; ++i) {
        const Square obstacle = obstacles[i];

        const int delta_r = obstacle.r - queen.r;
        const int delta_c = obstacle.c - queen.c;

        if (delta_r == 0) {
            // Same row
            if (delta_c > 0) {
                rgt.push(std::abs(delta_c) - 1);

            } else if (delta_c < 0) {
                lft.push(std::abs(delta_c) - 1);
            }
        } else if (delta_c == 0) {
            // Same column
            if (delta_r > 0) {
                upp.push(std::abs(delta_r) - 1);

            } else if (delta_r < 0) {
                dwn.push(std::abs(delta_r) - 1);
            }
        } else if (std::abs(delta_r) == std::abs(delta_c)) {
            // Same diagonal
            if (delta_r > 0 && delta_c > 0) {
                upr.push(std::abs(delta_r) - 1);

            } else if (delta_r < 0 && delta_c > 0) {
                dwr.push(std::abs(delta_r) - 1);

            } else if (delta_r < 0 && delta_c < 0) {
                dwl.push(std::abs(delta_r) - 1);

            } else if (delta_r > 0 && delta_c < 0) {
                upl.push(std::abs(delta_r) - 1);
            }
        }
    }

    // We will check to see if any obstacle on each path
    // If there isn't, the queen can move up to the end of the board
    const int count_upp = upp.empty()? n - queen.r :  upp.top();
    const int count_dwn = dwn.empty()? queen.r - 1 :  dwn.top();
    const int count_rgt = rgt.empty()? n - queen.c :  rgt.top();
    const int count_lft = lft.empty()? queen.c - 1 :  lft.top();

    const int count_upr = upr.empty()? std::min(n - queen.r, n - queen.c) :  upr.top();
    const int count_dwr = dwr.empty()? std::min(queen.r - 1, n - queen.c) :  dwr.top();
    const int count_dwl = dwl.empty()? std::min(queen.r - 1, queen.c - 1) :  dwl.top();
    const int count_upl = upl.empty()? std::min(n - queen.r, queen.c - 1) :  upl.top();

    // We return the sum of all paths
    return count_upp + count_dwn + count_rgt + count_lft + count_upr + count_upl + count_dwr + count_dwl;
}


int main()
{
    const Square queen {4, 3};
    std::vector<Square> obstacles {Square{5, 5}, Square{4, 2}, Square{2, 3}};
    const int nb_sq = queensAttack(5, 3, queen, obstacles);

    std::cout << nb_sq << std::endl; // Expected output : 10

    return 0;
}
