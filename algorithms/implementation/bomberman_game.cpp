/*
 * https://www.hackerrank.com/challenges/bomber-man/problem
 */

#include <iostream>
#include <vector>
#include <string>


/*
 * @param n: the number of time steps after the start of the game
 * @param grid: The game's grid
 */
void bomberMan(int n, std::vector<std::string>& grid)
{
    if (n <= 1) {
        return;
    }

    // There are only 4 possibilities of grids because
    // they will cycle eventually, so it's not necessary
    // to fully simulate up to n, just know which
    // case we are in
    for (int t = 2; t <= 2 + (n - 2) % 4; ++t) {
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (t % 2 != 0) {
                    // Bomberman does nothing but bombs explode
                    if (grid[i][j] == 'O') {
                        grid[i][j] = 'x';

                        if (0 < i) {
                            grid[i - 1][j] = 'x';
                        }
                        if (0 < j) {
                            grid[i][j - 1] = 'x';
                        }
                        if (i < grid.size() - 1 && grid[i + 1][j] != 'O') {
                            grid[i + 1][j] = 'x';
                        }
                        if (j < grid[i].size() - 1 && grid[i][j + 1] != 'O') {
                            grid[i][j + 1] = 'x';
                        }
                    }
                } else {
                    // Bomberman plants bombs and timer runs still
                    switch (grid[i][j]) {
                    case 'x':
                    case '.': grid[i][j] = 'p'; break;
                    case 'p': grid[i][j] = 'O'; break;
                    default: break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == 'p') {
                grid[i][j] = 'O';
            } else if (grid[i][j] == 'x') {
                grid[i][j] = '.';
            }
        }
    }
}

int main()
{
    const int n = 3;
    std::vector<std::string> grid {".......", "...O...", "....O.."
                                   ".......", "OO.....", "OO....."};

    bomberMan(n, grid);

    for (const auto& row : grid) {
        std::cout << row << "\n";
    }

    /* Expected output:
     * OOO.OOO
     * OO...OO
     * OOO...O
     * ..OO.OO
     * ...OOOO
     * ...OOOO
     */

    return 0;
}
