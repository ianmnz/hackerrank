/**
 * https://www.hackerrank.com/challenges/the-grid-search/problem
 */

#include <iostream>
#include <vector>
#include <string>


/**
 * @param G Grid of strings
 * @param P Pattern to look for
 * @return True if pattern found. False otherwise
 */
bool gridSearch(const std::vector<std::string>& G,
                const std::vector<std::string>& P)
{
    const int R = G.size(), C = G[0].length();
    const int r = P.size(), c = P[0].length();

    /**
     * Checks if pattern can be found front index (I, J)
     * @param I Row index of the grid
     * @param J Column index of the grid
     * @return True if pattern found. False otherwise
     */
    auto is_pattern_found = [r, c, &G, &P] (const int I, const int J)
    {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (G[I + i][J + j] != P[i][j]) {
                    return false;
                }
            }
        }
        return true;
    };

    // Checks for each pair (I, J) if pattern can be found
    for (int I = 0; I <= R - r; ++I) {
        for (int J = 0; J <= C - c; ++J) {
            if (is_pattern_found(I, J)) {
                return true;
            }
        }
    }

    return false;
}


int main()
{
    const std::vector<std::string> grid = {"7283455864",
                                           "6731158619",
                                           "8988242643",
                                           "3830589324",
                                           "2229505813",
                                           "5633845374",
                                           "6473530293",
                                           "7053106601",
                                           "0834282956",
                                           "4607924137"};

    const std::vector<std::string> pattern = {"9505",
                                              "3845",
                                              "3530"};

    std::cout << (gridSearch(grid, pattern)? "YES" : "NO") << std::endl;  // Expected output: YES

    return 0;
}
