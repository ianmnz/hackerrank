/**
 * https://www.hackerrank.com/challenges/is-binary-search-tree/problem
 */


struct Node
{
    int data;
    Node* left;
    Node* right;
};

bool checkBST(Node* const root)
{
    // There's no need to check for leaves
    // because of this return
    if (!root) {
        return true;
    }

    // To avoid a second parameter,
    // we use static
    // Always point to the first node
    // to its up-left
    static Node* prev = nullptr;

    if (!checkBST(root->left)) {
        return false;
    }

    // Check if they are in order
    if (prev && root->data <= prev->data) {
        return false;
    }

    prev = root;
    return checkBST(root->right);
}
