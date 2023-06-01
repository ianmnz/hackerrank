/**
 * https://www.hackerrank.com/challenges/red-knights-shortest-path/problem
 */


#include <iostream>
#include <string>
#include <queue>


/**
 * Convenient structure to keep track
 * of the current path and its length
 */
struct Move
{
    Move(int x, int y, int l, std::string&& p) : i(x), j(y), len(l), path(p) {}
    int i, j;
    int len;
    std::string path;
};

/**
 * @param n: Size of the n x n grid
 * @param i_start: Starting row
 * @param j_start: Starting column
 * @param i_end: Ending row
 * @param j_end: ending column
 */
void printShortestPath(const int n,
                       const int i_start, const int j_start,
                       const int i_end, const int j_end)
{
    if (i_start == i_end && j_start == j_end) {
        std::cout << "0" << std::endl;
        return;
    }

    auto isMoveValid = [n](const int i, const int j)
    {
        return (0 <= i && i < n && 0 <= j && j < n);
    };

    auto index = [n](const int i, const int j)
    {
        return (i * n) + j;
    };

    // Initializes with false
    bool* visited = new bool[n * n];

    // We do a BFS starting from the Start point
    // until we reach the End point
    std::queue<Move> moves;
    moves.push(Move(i_start, j_start, 0, ""));

    while (!moves.empty()) {
        Move move = moves.front();
        const int i = move.i;
        const int j = move.j;
        const int l = move.len;
        const std::string path = move.path;

        if (i == i_end && j == j_end) {
            break;
        }

        moves.pop();

        if (visited[index(i, j)]) {
            continue;
        }

        visited[index(i, j)] = true;

        if (isMoveValid(i - 2, j - 1) && !visited[index(i - 2, j - 1)]) {
            moves.push(Move(i - 2, j - 1, l + 1, path + "UL "));
        }

        if (isMoveValid(i - 2, j + 1) && !visited[index(i - 2, j + 1)]) {
            moves.push(Move(i - 2, j + 1, l + 1, path + "UR "));
        }

        if (isMoveValid(i, j + 2) && !visited[index(i, j + 2)]) {
            moves.push(Move(i, j + 2, l + 1, path + "R "));
        }

        if (isMoveValid(i + 2, j + 1) && !visited[index(i + 2, j + 1)]) {
            moves.push(Move(i + 2, j + 1, l + 1, path + "LR "));
        }

        if (isMoveValid(i + 2, j - 1) && !visited[index(i + 2, j - 1)]) {
            moves.push(Move(i + 2, j - 1, l + 1, path + "LL "));
        }

        if (isMoveValid(i, j - 2) && !visited[index(i, j - 2)]) {
            moves.push(Move(i, j - 2, l + 1, path + "L "));
        }
    }

    if (!moves.empty()) {
        std::cout << moves.front().len << std::endl;
        std::cout << moves.front().path << std::endl;

    } else {
        std::cout << "Impossible" << std::endl;
    }

    delete [] visited;
}


int main()
{
    const int n = 7;
    const int start_i = 6;
    const int start_j = 6;

    const int end_i = 0;
    const int end_j = 1;

    // Expected output:
    // 4
    // UL UL UL L
    printShortestPath(n, start_i, start_j, end_i, end_j);

    return 0;
}
