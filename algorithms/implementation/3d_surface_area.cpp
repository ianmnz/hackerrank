/*
 * https://www.hackerrank.com/challenges/3d-surface-area/problem
 */

#include <iostream>
#include <vector>

/*
 * @param A: Matrix with the height of each entry (i,j)
 * @return: The value of the 3D surface area
 */
int surfaceArea(const std::vector<std::vector<int>> A)
{
    const int H = A.size();
    const int W = A[0].size();

    // We add the surface seen from top and bottom
    int cost = 2 * H * W;

    // We add then the surface seen from left and right
    for (int i = 0; i < H; ++i) {
        int prev_row_val = 0;
        int row_accumulate = 0;

        for (int j = 0; j < W; ++j) {
            row_accumulate += std::abs(A[i][j] - prev_row_val);
            prev_row_val = A[i][j];
        }
        row_accumulate += A[i][W - 1];
        cost += row_accumulate;
    }

    // And finally, we add the surface seen from down and up
    for (int j = 0; j < W; ++j) {
        int prev_col_val = 0;
        int col_accumulate = 0;

        for (int i = 0; i < H; ++i) {
            col_accumulate += std::abs(A[i][j] - prev_col_val);
            prev_col_val = A[i][j];
        }
        col_accumulate += A[H - 1][j];
        cost += col_accumulate;
    }

    return cost;
}

int main()
{
    std::vector<std::vector<int>> A {{1, 3, 4}, {2, 2, 3}, {1, 2, 4}};
    std::cout << surfaceArea(A) << std::endl;   // Expected output : 60
    return 0;
}