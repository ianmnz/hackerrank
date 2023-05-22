/**
 * https://www.hackerrank.com/challenges/bfsshortreach/problem
 */

#include <iostream>
#include <vector>
#include <set>
#include <queue>


/**
 * @param n: Number of vertices
 * @param m: Number of edges
 * @param edges: Graph in a edge-like structure
 * @param s: Starting point
 * @return: The respective distance to the starting point
 */
std::vector<int> bfs(const int n, const int m, const std::vector<std::vector<int>>& edges, const int s)
{
    std::vector<std::set<int>> graph(n, std::set<int>());

    for (auto& edge : edges) {
        const int n1 = edge[0] - 1;
        const int n2 = edge[1] - 1;

        graph[n1].insert(n2);
        graph[n2].insert(n1);
    }

    std::vector<int> distances(n, -1);
    std::vector<bool> visited(n, false);

    std::queue<int> q;
    visited[s - 1] = true;
    distances[s - 1] = 0;
    q.push(s - 1);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (auto adj : graph[curr]) {
            if (!visited[adj]) {
                visited[adj] = true;
                distances[adj] = distances[curr] + 6;
                q.push(adj);
            }
        }
    }

    distances.erase(distances.begin() + (s - 1));

    return distances;
}


int main()
{
    const int n = 5, m = 3, s = 1;
    const std::vector<std::vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}};

    std::vector<int> output = bfs(n, m, edges, s);

    // Expected output: 6 6 12 -1
    for (auto distance : output) {
        std::cout << distance << " ";
    }
    std::cout << std::endl;

    return 0;
}
