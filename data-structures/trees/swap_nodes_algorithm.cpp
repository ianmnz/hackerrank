/**
 * https://www.hackerrank.com/challenges/swap-nodes-algo/problem
 */

#include <iostream>
#include <vector>


/**
 * @param tree: Array of nodes that form the tree
 * @param k: The Kth depth to swap
 * @param root: The subtree's root
 * @param depth: The root's depth
 * @param inOrder: Array with in-order tree
 */
void swap_subtree(std::vector<std::vector<int>>& tree, const int k, const int root, const int depth, std::vector<int>& inOrder)
{
    if (depth % k == 0) {
        const int aux = tree[root - 1][0];
        tree[root - 1][0] = tree[root - 1][1];
        tree[root - 1][1] = aux;
    }

    const int left = tree[root - 1][0];
    const int right = tree[root - 1][1];

    if (left > 0) {
        swap_subtree(tree, k, left, depth + 1, inOrder);
    }

    inOrder.push_back(root);

    if (right > 0) {
        swap_subtree(tree, k, right, depth + 1, inOrder);
    }
}

/**
 * @param tree: Array of nodes that form the tree
 * @param queries: Array with the depths K to swap
 * @return Array with in-order tree after each swap
 */
std::vector<std::vector<int>> swapNodes(std::vector<std::vector<int>>& tree, const std::vector<int>& queries)
{
    std::vector<std::vector<int>> res(queries.size(), std::vector<int>());

    for (int i = 0; i < queries.size(); ++i) {
        swap_subtree(tree, queries[i], 1, 1, res[i]);
    }
    return res;
}


int main()
{
    std::vector<std::vector<int>> tree {{2, 3}, {-1, 4}, {-1, 5}, {-1, -1}, {-1, -1}};
    const std::vector<int> queries {1, 2};

    std::vector<std::vector<int>> res = swapNodes(tree, queries);

    // Expected output :
    // 2 4 1 3 5
    // 4 2 1 5 3
    for (auto& inOrder : res) {
        for (auto node : inOrder) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
