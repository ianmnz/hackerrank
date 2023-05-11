/**
 * https://www.hackerrank.com/challenges/primsmstsub/problem
 */

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

/*
 * @param nodes: Set with visited nodes
 * @param n_fr: Array with the first node of the i-th edge
 * @param n_to: Array with the second node of the i-th edge
 * @return: true if exactly one of the nodes is in the set
 */
bool only_one_node_in_set(const std::set<int>& nodes, const int n_fr, const int n_to)
{
    const bool n_fr_in_set = (nodes.find(n_fr) != nodes.end());
    const bool n_to_in_set = (nodes.find(n_to) != nodes.end());

    if (n_fr_in_set && !n_to_in_set) {
        return true;

    } else if (!n_fr_in_set && n_to_in_set) {
        return true;

    } else {
        return false;
    }
}

/*
 * @param n: Number of nodes
 * @param edges: The graph in a edge-based structure
 * @param start: Starting node of the algorithm
 * @return: Weight of the subtree
 */
int prims(const int n, std::vector<std::vector<int>>& edges, const int start)
{
    // We sort the graph by edge weight in ascending order
    std::sort(edges.begin(), edges.end(),
              [](const std::vector<int>& lhs, const std::vector<int>& rhs)
              { return lhs[2] < rhs[2]; });

    std::set<int> nodes_added {start};
    int tree_weight = 0;

    // We iterate until having added all nodes
    while (nodes_added.size() < n) {
        for (const auto& edge : edges) {
            const int n_fr = edge[0];
            const int n_to = edge[1];
            const int e_wt = edge[2];

            // We only insert edges that would add a new node to the subtree
            // Since the graph is sorted, we can break here our search
            if (only_one_node_in_set(nodes_added, n_fr, n_to)) {
                nodes_added.insert(n_fr);
                nodes_added.insert(n_to);
                tree_weight += e_wt;
                break;
            }
        }
    }

    return tree_weight;
}


int main()
{
    const int n = 5;
    const int start = 1;
    std::vector<std::vector<int>> edges {{1, 2, 3}, {1, 3, 4}, {4, 2, 6}, {5, 2, 2}, {2, 3, 5}, {3, 5, 7}};

    std::cout << prims(n, edges, start) << std::endl;   // Expected output: 15

    return 0;
}
