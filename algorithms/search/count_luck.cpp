/**
 * https://www.hackerrank.com/challenges/count-luck/problem
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>


struct Cell
{
    Cell(int i, int j, int n) : x(i), y(j), nb_forks(n) {}

    int x;
    int y;
    int nb_forks;
};

/**
 * @param matrix 2D array with the grid
 * @param k The guessed value of bifurcations
 * @return True if guessed right, false otherwise
 */
bool countLuck(std::vector<std::string>& matrix, const int k)
{
    const int n = matrix.size();
    const int m = matrix[0].length();

    auto is_valid = [n, m](const int i, const int j)
    {
        return 0 <= i && i < n && 0 <= j && j < m;
    };

    std::stack<Cell> dfs;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 'X' || matrix[i][j] == '*') {
                continue;
            }

            // We count the number of possible directions
            // from point (i,j)
            int fork = 0;

            // Up
            if (is_valid(i - 1, j) && matrix[i - 1][j] != 'X') {
                fork++;
            }

            // Down
            if (is_valid(i + 1, j) && matrix[i + 1][j] != 'X') {
                fork++;
            }

            // Left
            if (is_valid(i, j - 1) && matrix[i][j - 1] != 'X') {
                fork++;
            }

            // Right
            if (is_valid(i, j + 1) && matrix[i][j + 1] != 'X') {
                fork++;
            }

            // We start our DFS with the starting point M
            // and count it as a fork for when starting
            // and having at least 2 directions to go
            if (matrix[i][j] == 'M') {
                fork++;
                dfs.push(Cell(i, j, 0));
            }

            // (i,j) is a bifurcation at least: it forks
            // and we mark it on the grid
            if (fork > 2) {
                matrix[i][j] = 'Y';
            }
        }
    }

    // DFS
    while (!dfs.empty()) {
        Cell curr = dfs.top();
        const char cell = matrix[curr.x][curr.y];

        if (cell == '*') {
            break;
        }

        dfs.pop();

        if (cell == '0') {
            continue;
        }
        matrix[curr.x][curr.y] = '0';

        int nb_forks = curr.nb_forks;
        if (cell == 'Y') {
            nb_forks++;
        }

        // Up
        if (is_valid(curr.x - 1, curr.y) && matrix[curr.x - 1][curr.y] != 'X') {
            dfs.push(Cell(curr.x - 1, curr.y, nb_forks));
        }

        // Down
        if (is_valid(curr.x + 1, curr.y) && matrix[curr.x + 1][curr.y] != 'X') {
            dfs.push(Cell(curr.x + 1, curr.y, nb_forks));
        }

        // Left
        if (is_valid(curr.x, curr.y - 1) && matrix[curr.x][curr.y - 1] != 'X') {
            dfs.push(Cell(curr.x, curr.y - 1, nb_forks));
        }

        // Right
        if (is_valid(curr.x, curr.y + 1) && matrix[curr.x][curr.y + 1] != 'X') {
            dfs.push(Cell(curr.x, curr.y + 1, nb_forks));
        }
    }

    return dfs.top().nb_forks == k;
}


int main()
{
    const int k = 3;
    std::vector<std::string> matrix {".X.X......X"
                                     ".X*.X.XXX.X"
                                     ".XX.X.XM..."
                                     "......XXXX."};

    std::cout << (countLuck(matrix, k) ? "Impressed" : "Oops!" ) << std::endl;   // Expected output: Impressed
    return 0;
}
