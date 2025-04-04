/**
 * https://www.hackerrank.com/challenges/coin-on-the-table/problem
 */

#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

constexpr std::array<std::tuple<char, int, int>, 4> directions{
    std::tuple{'U', -1, 0},  // up
    std::tuple{'D',  1, 0},  // down
    std::tuple{'L', 0, -1},  // left
    std::tuple{'R',  0, 1}   // right
};

/**
 * @param n Nb of rows
 * @param m Nb of colones
 * @param board Array of each row of the board
 * @return The row and colone of the target
 */
std::pair<int, int> find_target(const int n, const int m,
                                const std::vector<std::string> &board)
{
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (board[r][c] == '*') {
                return {r, c};
            }
        }
    }
    return {-1, -1};
}

/**
 * @param n Nb of rows
 * @param m Nb of colones
 * @param k Max number of steps
 * @param board Array of each row of the board
 * @return The minimum cost to reach the target if possible.
 * @return -1 otherwise
 */
int coinOnTheTable(const int n, const int m, const int k,
                   const std::vector<std::string> &board)
{
    const auto &[r, c] = find_target(n, m, board);

    if (r < 0) return -1;

    std::vector<std::vector<int>> costs(n,
        std::vector<int>(m, std::numeric_limits<int>::max()));
    costs[0][0] = 0;

    // x-pos, y-pos, time step, cost
    std::queue<std::array<int, 4>> q;
    q.push({0, 0, 0, 0});

    while (!q.empty()) {
        const auto& [x, y, t, c] = q.front();
        q.pop();

        if (t >= k) {
            // too many steps
            continue;
        }

        const char move = board[x][y];

        for (const auto &[dir, dx, dy] : directions) {
            const int nx = x + dx;
            const int ny = y + dy;

            if (nx < 0 || n <= nx) {
                // out-of-range : rows
                continue;
            }

            if (ny < 0 || m <= ny) {
                // out-of-range : cols
                continue;
            }

            const int nc = c + (dir != move);

            if (nc < costs[nx][ny]) {
                costs[nx][ny] = nc;
                q.push({nx, ny, t + 1, nc});
            }
        }
    }

    return costs[r][c] < std::numeric_limits<int>::max() ? costs[r][c] : -1;
}

int main()
{
    const int n = 2;
    const int m = 2;
    const int k = 3;
    const std::vector<std::string> board{"UDL",
                                         "RR*"};

    std::cout << coinOnTheTable(n, m, k, board) << std::endl;  // Expected output: 1

    return 0;
}
