/**
 * https://www.hackerrank.com/challenges/castle-on-the-grid/problem
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>


struct Cell
{
    Cell(int X, int Y, int moves = 0) : x(X), y(Y), nb_moves(moves) {}
    int x;
    int y;
    int nb_moves;
};

/**
 * @param grid: The 2D array containing the grid
 * @param startX: The starting position's X
 * @param startX: The starting position's Y
 * @param startX: The goal position's X
 * @param startX: The goal position's Y
 * @return: The minimum number of moves necessary to reach the goal from the start
*/
int minimumMoves(const std::vector<std::string>& grid,
                 const int startX, const int startY,
                 const int goalX, const int goalY)
{
    if (startX == goalX && startY == goalY) {
        return 0;
    }

    const int n = grid.size();

    // Lambda function that returns the index
    // in the vector given the position X,Y in the grid
    auto index = [n](int X, int Y)
    {
        return (X * n) + Y;
    };

    // Lambda function that returns a boolean:
    // true if the cell is inside the grid and is not X
    // false otherwise
    auto is_valid = [n, &grid](int X, int Y)
    {
        if (0 <= X && X < n && 0 <= Y && Y < n) {
            return grid[X][Y] != 'X';
        }
        return false;
    };

    std::queue<Cell> bfs;
    std::vector<bool> visited(n * n, false);

    visited[index(startX, startY)] = true;
    bfs.push(Cell(startX, startY));

    int moves, x, y;
    while(!bfs.empty()) {
        Cell curr = bfs.front();
        bfs.pop();

        // If we reached the goal, return the number
        // of moves up to here. Since it is a BFS,
        // the returned value is the minimum
        if (curr.x == goalX && curr.y == goalY) {
            return curr.nb_moves;
        }

        moves = curr.nb_moves;

        // The main idea here is to search all nodes in
        // a given direction (up, down, left, right) up
        // to the end of the grid or if a 'X' is found.
        // We only add to the queue if it is not already visited

        // Up
        x = curr.x - 1;
        y = curr.y;
        while(is_valid(x, y)) {
            if (!visited[index(x, y)]) {
                visited[index(x, y)] = true;
                bfs.push(Cell(x, y, moves + 1));
            }
            x--;
        }

        // Down
        x = curr.x + 1;
        y = curr.y;
        while(is_valid(x, y)) {
            if (!visited[index(x, y)]) {
                visited[index(x, y)] = true;
                bfs.push(Cell(x, y, moves + 1));
            }
            x++;
        }

        // Left
        x = curr.x;
        y = curr.y - 1;
        while(is_valid(x, y)) {
            if (!visited[index(x, y)]) {
                visited[index(x, y)] = true;
                bfs.push(Cell(x, y, moves + 1));
            }
            y--;
        }

        // Right
        x = curr.x;
        y = curr.y + 1;
        while(is_valid(x, y)) {
            if (!visited[index(x, y)]) {
                visited[index(x, y)] = true;
                bfs.push(Cell(x, y, moves + 1));
            }
            y++;
        }
    }
    return -1;
}


int main()
{
    const std::vector<std::string> grid = {
        ".X.",
        ".X.",
        "..."
    };

    const int startX = 0, startY = 0;
    const int goalX = 0, goalY = 0;

    std::cout << minimumMoves(grid, startX, startY, goalX, goalY) << std::endl; // Expected output: 3

    return 0;
}
