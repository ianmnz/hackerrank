/**
 * https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
 */

#include <iostream>
#include <vector>


/**
 * @param i Row index
 * @param j Column index
 * @param region Region number
 * @param matrix Array with the values to be filled
 * @return The size of the region
 */
int recursive_fill(const int i, const int j, const int region,
                   std::vector<std::vector<int>>& matrix)
{
    if (i < 0 || j < 0 || i >= matrix.size() || j >= matrix[0].size()) {
        return 0;
    }

    if (matrix[i][j] <= 0) {
        return 0;
    }

    int region_size = 1;
    matrix[i][j] = -region;

    region_size += recursive_fill(i - 1, j, region, matrix);    // up
    region_size += recursive_fill(i + 1, j, region, matrix);    // down

    region_size += recursive_fill(i, j - 1, region, matrix);    // left
    region_size += recursive_fill(i, j + 1, region, matrix);    // right

    region_size += recursive_fill(i - 1, j - 1, region, matrix);    // up-left
    region_size += recursive_fill(i + 1, j - 1, region, matrix);    // down-left

    region_size += recursive_fill(i - 1, j + 1, region, matrix);    // up-right
    region_size += recursive_fill(i + 1, j + 1, region, matrix);    // down-right

    return region_size;
}

/**
 * @param matrix Array of 0's and 1's defining regions
 * @return The size of the biggest region
 */
int connectedCell(std::vector<std::vector<int>>& matrix)
{
    const int n = matrix.size();
    const int m = matrix[0].size();

    int nb_regions = 0;
    int max_region_size = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 1) {
                // If a new region is found, we fill it with
                // the next available region number
                const int region_size = recursive_fill(i, j, ++nb_regions, matrix);
                max_region_size = std::max(max_region_size, region_size);
            }
        }
    }

    return max_region_size;
}


int main()
{
    std::vector<std::vector<int>> matrix {{1, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}};
    std::cout << connectedCell(matrix) << std::endl;    // Expected output: 5

    return 0;
}
