/**
 * https://www.hackerrank.com/challenges/contacts/problem
 */

#include <iostream>
#include <vector>
#include <string>


struct TrieNode
{
    TrieNode()
    {
        nbWords = 0;
        isWord = false;

        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }

    ~TrieNode()
    {
        for (int i = 0; i < 26; ++i) {
            if (children[i]) {
                delete children[i];
            }
        }
    }

    int nbWords;            // How many words use this node
    bool isWord;            // If it is a word
    TrieNode* children[26]; // The 26 lowercase English letters
};

/**
 * @param root: The root node of the Trie
 * @param word: The word to be inserted
 */
void insert(TrieNode* const root, const std::string& word)
{
    TrieNode* curr = root;

    for (char c : word) {
        const int idx = c - 'a';

        if (!curr->children[idx]) {
            curr->children[idx] = new TrieNode();
        }
        curr = curr->children[idx];
        curr->nbWords++;
    }
    curr->isWord = true;
}

/**
 * @param root: The root of the Trie
 * @param seq: The sequence to look for
 */
int search(TrieNode* const root, const std::string& seq)
{
    TrieNode* curr = root;

    for (auto c : seq) {
        const int idx = c - 'a';

        if (!curr->children[idx]) {
            return 0;
        }
        curr = curr->children[idx];
    }

    return curr->nbWords;
}
