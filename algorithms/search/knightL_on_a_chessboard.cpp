/**
 * https://www.hackerrank.com/challenges/knightl-on-chessboard/problem
 */

#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>


struct Node {
    int x;
    int y;
    int t;
};


/**
 * @param x Current x position
 * @param y Current y position
 * @param a Small movement length
 * @param b Big movement length
 * @return List of next positions starting from (x,y)
 */
std::vector<std::pair<int, int>> next_moves(const int x, const int y,
                                            const int a, const int b)
{
    return {{x - a, y - b}, {x - a, y + b},
            {x + a, y - b}, {x + a, y + b},

            {x - b, y - a}, {x - b, y + a},
            {x + b, y - a}, {x + b, y + a}};
}


/**
 * @param x Current x position
 * @param y Current y position
 * @param n Chessboard size
 * @return true if inside board,
 * @return false otherwise
 */
bool is_valid(const int x, const int y, const int n)
{
    return (0 <= x && x < n) && (0 <= y && y < n);
}

/**
 * @param n Chessboard size
 * @param a Small movement length
 * @param b Big movement length
 * @return int The minimum nb of moves to reach the other end of the board
 */
int bfs(const int n, const int a, const int b)
{
    std::queue<Node> q;
    q.push({0, 0, 0});

    std::set<std::pair<int, int>> visited;

    while (!q.empty()) {
        auto [x, y, t] = q.front();
        q.pop();

        if (visited.find({x, y}) != visited.end()) {
            continue;
        }

        visited.insert({x, y});

        for (auto [nx, ny] : next_moves(x, y, a, b)) {
            if (!is_valid(nx, ny, n)) {
                continue;
            }

            if (nx == n - 1 && ny == nx) {
                // Reached end of the board
                return t + 1;
            }

            q.push({nx, ny, t + 1});
        }
    }

    return -1;
}

/**
 * @param n Chessboard size
 * @return A matrix of the minimum nb of moves to reach the end of the board for each (a, b) combination
 */
std::vector<std::vector<int>> knightLOnAChessboard(const int n)
{
    std::vector<std::vector<int>> res(n - 1, std::vector<int>(n - 1));

    for (int i = 0; i < n - 1; ++i) {
        res[i][i] = bfs(n, i + 1, i + 1);

        for (int j = i + 1; j < n - 1; ++j) {
            res[i][j] = bfs(n, i + 1, j + 1);
            res[j][i] = res[i][j];
        }
    }

    return res;
}


int main()
{
    const int n = 5;
    const auto res = knightLOnAChessboard(n);

    /*
    Expected output:
    4  4  2  8
    4  2  4  4
    2  4 -1 -1
    8  4 -1  1
    */
    for (auto& row : res) {
        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    return 0;
}
