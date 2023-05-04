/*
 * https://www.hackerrank.com/challenges/kruskalmstrsub/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/*
 * @param g_fr: Array with the first node of the i-th edge
 * @param g_to: Array with the second node of the i-th edge
 * @param g_wt: Array with the weight node of the i-th edge
 * @return: Sorted array of edges in ascending order
 */
std::vector<std::vector<int>> sort(std::vector<int>& g_fr, std::vector<int>& g_to, std::vector<int>& g_wt)
{
    const int n = g_wt.size();

    std::vector<std::vector<int>> edges;

    for (int i = 0; i < n; ++i) {
        edges.push_back({g_wt[i], g_fr[i], g_to[i]});
    }

    // Sort edge by weight
    std::sort(edges.begin(), edges.end());

    return edges;
}

/*
 * Disjoint sets algorithm : find
 * @param root: Root vector
 * @param i: Node to find the root
 * @return: i's root node
 */
int find(std::vector<int>& root, int v) {
    if (root[v] == v) {
        return v;
    } else {
        root[v] = find(root, root[v]);
        return root[v];
    }
}

/*
 * Disjoint sets algorithm : union
 * @param root: Root vector
 * @param i: Left node
 * @param j: Right node
 */
void unite(std::vector<int>& root, int v, int u) {
    int root_v = find(root, v);
    int root_u = find(root, u);

    if (root_v != root_u) {
        root[root_u] = root_v;
        root[u] = root_v;
    }
}

/*
 * @param g_nodes: Number of nodes
 * @param g_from: Array with the first node of the i-th edge
 * @param g_to: Array with the second node of the i-th edge
 * @param g_weight: Array with the weight node of the i-th edge
 * @return: Weight of the subtree
 */
long long kruskals(int g_nodes, std::vector<int> g_from, std::vector<int> g_to, std::vector<int> g_weight)
{
    long long tree_weight = 0ll;

    std::vector<int> root(g_nodes);
    std::iota(root.begin(), root.end(), 0);

    std::vector<std::vector<int>> edges = sort(g_from, g_to, g_weight);

    // We will add edges to our disjoint set
    // in ascending order of weight. Doing so,
    // we will find the Minimum Spanning Tree
    int count = g_nodes - 1;
    for (int i = 0; i < edges.size(); ++i) {
        int v = edges[i][1];
        int u = edges[i][2];
        int w = edges[i][0];

        if (find(root, v - 1) != find(root, u - 1)) {
            unite(root, v - 1, u - 1);
            tree_weight += (long long) w;
            --count;
        }

        if (count == 0) {
            break;
        }
    }

    return tree_weight;
}


int main()
{
    const int g_nodes = 4;
    const std::vector<int> g_from {1, 1, 4, 2, 3, 3};
    const std::vector<int> g_to {2, 3, 1, 4, 2, 4};
    const std::vector<int> g_weight {5, 3, 6, 7, 4, 5};

    const long long mst_weight = kruskals(g_nodes, g_from, g_to, g_weight);
    std::cout << mst_weight << std::endl;   // Expected output: 12

    return 0;
}
