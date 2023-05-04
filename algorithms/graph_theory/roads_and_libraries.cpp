/*
 * https://www.hackerrank.com/challenges/torque-and-development/problem
 */

#include <iostream>
#include <vector>
#include <numeric>

/*
 * Disjoint sets algorithm : find
 * @param root: Root vector
 * @param i: Node to find the root
 * @return: i's root node
 */
int find(std::vector<int>& root, int i)
{
    if (root[i] == i) {
        return i;
    } else {
        root[i] = find(root, root[i]);
        return root[i];
    }
}

/*
 * Disjoint sets algorithm : union
 * @param root: Root vector
 * @param i: Left node
 * @param j: Right node
 */
void unite(std::vector<int>& root, int i, int j)
{
    int root_i = find(root, i);
    int root_j = find(root, j);

    if (root_i != root_j) {
        root[root_j] = root_i;
    }
}

/*
 * Minimum spanning tree
 * @param n: Number of nodes of the graph
 * @param edges: Graph described by its edges
 * @return: Size of the maximum spanning tree
 */
long mst(int n, std::vector<std::vector<int>>& edges)
{
    long tree_size = 0l;

    std::vector<int> root(n);
    std::iota(root.begin(), root.end(), 0);

    for (const auto& edge : edges) {
        int v = edge[0];
        int u = edge[1];

        if (find(root, v - 1) != find(root, u - 1)) {
            unite(root, v - 1, u - 1);
            tree_size++;
        }
    }

    return tree_size;
}

/*
 * Depth fisrt search
 * @param visited: Visited nodes
 * @param adj: Graph described by adjancencies
 * @param i: Current node index
 */
void dfs(std::vector<bool>& visited, std::vector<std::vector<int>>& adj, int i)
{
    visited[i] = true;

    std::vector<int>::const_iterator it;
    for (it = adj[i].begin(); it != adj[i].end(); ++it) {
        if (!visited[*it]) {
            dfs(visited, adj, *it);
        }
    }
}

/*
 * Find graph's connected components using DFS
 * @param n: Number of nodes of the graph
 * @param edges: Graph described by its edges
 * @return: Number of connected components
 */
long connected_components(int n, std::vector<std::vector<int>>& edges)
{
    long nb_connected_comp = 0;
    std::vector<bool> visited(n, false);

    std::vector<std::vector<int>> adj (n, std::vector<int>());

    for (const auto& edge : edges) {
        int v = edge[0];
        int u = edge[1];

        adj[v - 1].push_back(u - 1);
        adj[u - 1].push_back(v - 1);
    }

    for (int v = 0; v < n; ++v) {
        if (!visited[v]) {
            dfs(visited, adj, v);
            nb_connected_comp++;
        }
    }

    return nb_connected_comp;
}

/*
 * @param n: Number of cities
 * @param c_lib: Cost of one library
 * @param c_road: Cost of one road
 * @param roads: Roads connecting roads[i][0] to roads[i][1]
 * @return: Minimum cost of building roads and libraries
 */
long roadsAndLibraries(int n, int c_lib, int c_road, std::vector<std::vector<int>> cities)
{
    // If building a road is more expensive than
    // building a library, it's better to just
    // build libraries
    long only_libs = (long) n * (long) c_lib;
    if (c_road > c_lib) {
        return only_libs;
    }

    // Otherwise find the MST:
    // That's the minimum number of roads necessary
    // to connect all cities
    long mstree_size = mst(n, cities);
    long cost_fix_roads = c_road * mstree_size;

    // Find all connected components
    // There's no need to build more than one library
    // by connected component
    long nb_conn_comp = connected_components(n, cities);
    long cost_build_libs = c_lib * nb_conn_comp;

    long max_cost = cost_build_libs + cost_fix_roads;

    return max_cost;
}


int main()
{
    const int n = 3, c_lib = 2, c_road = 1;
    std::vector<std::vector<int>> roads {{1, 2}, {3, 1}, {2, 3}};

    const long cost = roadsAndLibraries(n, c_lib, c_road, roads);

    std::cout << cost << std::endl; // Expected output: 4

    return 0;
}
