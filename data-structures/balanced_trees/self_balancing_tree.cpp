/**
 * https://www.hackerrank.com/challenges/self-balancing-tree/problem
 * https://en.wikipedia.org/wiki/AVL_tree
 */

#include <iostream>


struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
};

inline int height(const node * const root)
{
    if (!root) {
        return -1;
    }
    return root->ht;
}

node* right_rotate(node * const root)
{
    node* left = root->left;
    node* right = left->right;

    // Rotate
    left->right = root;
    root->left = right;

    // Update heights
    root->ht = 1 + std::max(height(root->left), height(root->right));
    left->ht = 1 + std::max(height(left->left), height(left->right));

    return left;
}

node* left_rotate(node * const root)
{
    node* right = root->right;
    node* left = right->left;

    // Rotate
    right->left = root;
    root->right = left;

    // Update heights
    root->ht = 1 + std::max(height(root->left), height(root->right));
    right->ht = 1 + std::max(height(right->left), height(right->right));

    return right;
}

node* insert(node * const root, const int val)
{
	if (!root) {
        node* leaf = new node();
        leaf->val = val;
        leaf->left = nullptr;
        leaf->right = nullptr;
        leaf->ht = 0;
        return leaf;
    }

    if (val < root->val) {
        root->left = insert(root->left, val);

    } else if (val > root->val) {
        root->right = insert(root->right, val);

    } else {
        return root;
    }

    const int ht_left = height(root->left);
    const int ht_right = height(root->right);

    root->ht = 1 + std::max(ht_left, ht_right);
    const int balanceFactor = ht_left - ht_right;

    // If balanceFactor is positive, then root->left exists
    // Else if it is negative, then root->right exists

    // Left left case
    if (balanceFactor > 1 && val < root->left->val) {
        return right_rotate(root);
    }

    // Right right case
    if (balanceFactor < -1 && val > root->right->val) {
        return left_rotate(root);
    }

    // Left right case
    if (balanceFactor > 1 && val > root->left->val) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // Right left case
    if (balanceFactor < -1 && val < root->right->val) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}
