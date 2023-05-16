/*
 * https://www.hackerrank.com/challenges/cut-the-tree/problem
 */

#include <iostream>
#include <vector>
#include <set>
#include <limits>


struct Node
{
    Node(const int idx, const int dt) : index(idx), data(dt), weight(dt) {}

    int index;
    int data;
    int weight;

    // Children and parent included
    std::set<Node*> neighbors = {};
};

struct Tree
{
    Tree(const int n) { nodes = std::vector<Node*>(n, nullptr); }

    ~Tree()
    {
        for (auto node : nodes) {
            delete node;
        }
    }

    Node* root = nullptr;
    std::vector<Node*> nodes;
};

/**
 * Preorder traversal algorithm
 * @param node: Node to increase weight
 * @param prev: Parent node
 */
void preorder(Node* node, const Node* prev)
{
    if (!node) {
        return;
    }

    for (auto& neighbor : node->neighbors) {
        // We avoid going back to the parent node
        if (neighbor == prev) {
            continue;
        }

        preorder(neighbor, node);

        // We increment the node's weight with those of its children
        node->weight += neighbor->weight;
    }
}

/**
 * @param data: Array with the data of each node
 * @param edges: Graph on a edge-like structure
 * @return The minimum absolute difference of two subtrees
 */
int cutTheTree(const std::vector<int>& data, const std::vector<std::vector<int>>& edges)
{
    Tree tree(data.size());

    tree.root = new Node(0, data[0]);
    tree.nodes[0] = tree.root;

    // We first create the tree
    for (const auto& edge : edges) {
        int n1 = edge[0] - 1;
        int n2 = edge[1] - 1;

        if (!tree.nodes[n1]) {
            tree.nodes[n1] = new Node(n1, data[n1]);
        }

        if (!tree.nodes[n2]) {
            tree.nodes[n2] = new Node(n2, data[n2]);
        }

        tree.nodes[n1]->neighbors.insert(tree.nodes[n2]);
        tree.nodes[n2]->neighbors.insert(tree.nodes[n1]);
    }

    // Than we traverse it by pre-ordering
    preorder(tree.root, nullptr);

    const int half_tree_weight = tree.root->weight/2;
    int min_diff_to_balance = std::numeric_limits<int>::max();
    int min_abs_diff_cut = 0;

    // Finally we compare the weight of each node with the half of the total weight of the tree
    // being close to 50% would mean a balanced cut
    for (int i = 1; i < data.size(); ++i) {
        const int diff_to_balance = std::abs(tree.nodes[i]->weight - half_tree_weight);

        if (diff_to_balance < min_diff_to_balance) {
            min_diff_to_balance = diff_to_balance;
            min_abs_diff_cut = std::abs(tree.root->weight - 2 * tree.nodes[i]->weight);
        }
    }

    return min_abs_diff_cut;
}


int main()
{
    const std::vector<int> data = {100, 200, 100, 500, 100, 600};
    const std::vector<std::vector<int>> edges = {{1, 2}, {2, 3}, {2, 5}, {4, 5}, {5, 6}};

    std::cout << cutTheTree(data, edges) << std::endl;  // Expected output: 400

    return 0;
}
