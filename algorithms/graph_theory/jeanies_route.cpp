/**
 * https://www.hackerrank.com/challenges/jeanies-route/problem
 */

#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <queue>


/**
 * @param destinations: Array with all the destinations
 * @param adjacency: Graph structured by adjacency nodes and weights
 * @param nodes_to_remove: Bitmask of nodes to exclude from graph
 */
void prune(const std::vector<int>& destinations,
           const std::map<int, std::map<int, int>>& adjacency,
           bool* nodes_to_remove)
{
    const int N = adjacency.size();

    int* degree = new int[N];
    bool* is_destination = new bool[N];

    for (int i = 0; i < N; ++i) {
        nodes_to_remove[i] = false;
        is_destination[i] = false;
        degree[i] = adjacency.at(i).size();
    }

    for (auto destination : destinations) {
        is_destination[destination - 1] = true;
    }

    std::stack<int> stk;
    for (int i = 0; i < N; ++i) {
        // If a leaf is not a destination,
        // we push it to the stack
        if (!is_destination[i] && degree[i] == 1) {
            stk.push(i);
        }
    }

    while (!stk.empty()) {
        const int leaf = stk.top();
        stk.pop();

        nodes_to_remove[leaf] = true;

        for (const auto& [neighbour, _] : adjacency.at(leaf)) {
            if (is_destination[neighbour]) {
                break;

            } else if (!nodes_to_remove[neighbour]) {
                if (--degree[neighbour] == 1) {
                    stk.push(neighbour);
                    break;
                }
            }
        }
    }

    delete[] degree;
    delete[] is_destination;
}

/**
 * Based on the Steiner tree problem
 * @param adjacency: Graph structured by adjacency nodes and weights
 * @param nodes_to_remove: Bitmask of nodes to exclude from graph
 * @param source: Starting node for the BFS. Becomes the opposite leaf
 * @return The diameter seeing from the source
 */
long find_diameter(const std::map<int, std::map<int, int>>& adjacency,
                   const bool* const nodes_to_remove,
                   int& source)
{
    const int N = adjacency.size();

    int* distances = new int[N];
    for (int i = 0; i < N; ++i) {
        distances[i] = -1;
    }
    distances[source] = 0;

    std::queue<int> q;
    q.push(source);

    long total = 0l;
    long diameter = 0l;

    while (!q.empty()) {
        const int curr = q.front();
        q.pop();

        for (const auto& [neighbour, weight] : adjacency.at(curr)) {
            if (!nodes_to_remove[neighbour] && distances[neighbour] < 0) {
                total += weight;
                q.push(neighbour);
                distances[neighbour] = distances[curr] + weight;

                if (distances[neighbour] > diameter) {
                    diameter = distances[neighbour];
                    source = neighbour;
                }
            }
        }
    }

    delete[] distances;
    // To take into account the weighted diameter of the graph,
    // we double the total weight of the graph and remove
    // the distance between source and target
    return 2l*total - diameter;
}

long jeanisRoute(const std::vector<int>& destinations,
                 const std::vector<std::vector<int>>& roads)
{
    std::map<int, std::map<int, int>> adjacency;
    for(auto& road : roads) {
        const int from = road[0];
        const int to = road[1];
        const int dist = road[2];

        adjacency[from - 1][to - 1] = dist;
        adjacency[to - 1][from - 1] = dist;
    }

    // We prune the nodes that are unnecessary:
    // leafs that are not destinations
    // branches that don't contain destinations
    bool* nodes_to_remove = new bool[adjacency.size()];
    prune(destinations, adjacency, nodes_to_remove);

    int source = destinations[0] - 1;

    // First call to find a distant leaf, second call to find the diameter as described here:
    // https://cs.stackexchange.com/questions/22855/algorithm-to-find-diameter-of-a-tree-using-bfs-dfs-why-does-it-work
    long res = find_diameter(adjacency, nodes_to_remove, source);
    res = find_diameter(adjacency, nodes_to_remove, source);

    delete[] nodes_to_remove;
    return res;
}


int main()
{
    const std::vector<int> destinations {1, 3, 4};
    const std::vector<std::vector<int>> roads {{1, 2, 1}, {2, 3, 2}, {2, 4, 2}, {3, 5, 3}};

    std::cout << jeanisRoute(destinations, roads) << std::endl; // Expected output: 6

    return 0;
}
