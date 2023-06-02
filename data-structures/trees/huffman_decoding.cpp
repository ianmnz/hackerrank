/**
 * https://www.hackerrank.com/challenges/tree-huffman-decoding/problem
 */

#include <string>


struct node {
    int freq;
    char data;
    node* left;
    node* right;
};

/**
 * Decode a Huffman tree
 * @param root: Root to the Huffman tree
 * @param encoded: Encoded string of 0 and 1
 * @return The decoded string
 */
std::string decode_huff(const node * const root, const std::string& encoded)
{
    std::string decoded = "";
    const node* curr = root;

    for (auto c : encoded) {
        if (c == '0') {
            if (curr->left->data != '\0') { // is leas
                decoded += curr->left->data;
                curr = root;

            } else {
                curr = curr->left;

            }
        } else {  // c == '1'
            if (curr->right->data != '\0') { // is leaf
                decoded += curr->right->data;
                curr = root;

            } else {
                curr = curr->right;
            }
        }
    }

    return decoded;
}
