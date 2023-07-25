/*
 * https://www.hackerrank.com/challenges/flipping-the-matrix/problem
 */

#include <iostream>
#include <vector>


/**
 * @param matrix: 2D array
 * @return The maximized sum of the upper-left quadrant
 */
int flippingMatrix(const std::vector<std::vector<int>>& matrix)
{
    const int n = matrix.size() / 2;
    int res = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            const int ul = matrix[i][j];
            const int ur = matrix[i][2*n - j - 1];
            const int dl = matrix[2*n - i - 1][j];
            const int dr = matrix[2*n - i - 1][2*n - j - 1];

            res += std::max(std::max(ul, ur), std::max(dl, dr));
        }
    }

    return res;
}


int main()
{
    const std::vector<std::vector<int>> matrix = {{112, 42, 83, 119},
                                                  {56, 125, 56, 49},
                                                  {15, 78, 101, 43},
                                                  {62, 98, 114, 108}};

    std::cout << flippingMatrix(matrix) << std::endl;   // Expected output: 414

    return 0;
}
