/**
 * https://www.hackerrank.com/challenges/sparse-arrays/problem
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>


const int ALPHABET_SIZE = 26;

struct TrieNode
{
    TrieNode()
    {
        for (int c = 0; c < ALPHABET_SIZE; ++c) {
            children[c] = nullptr;
        }
    }

    ~TrieNode()
    {
        for (auto c : children) {
            if (c) {
                delete c;
                c = nullptr;
            }
        }
    }

    TrieNode* children[ALPHABET_SIZE];
    int count = 0;
};

/**
 * @param root: The root node of the Trie
 * @param word: The word to be inserted
 */
void insert(TrieNode* const root, const std::string& word)
{
    TrieNode* curr = root;

    for (auto c : word) {
        const int idx = c - 'a';
        if (!curr->children[idx]) {
            curr->children[idx] = new TrieNode();
        }
        curr = curr->children[idx];
    }
    curr->count++;
}

/**
 * @param root: The root of the Trie
 * @param query: The query to look for
 * @return The number of instances of the query
 */
int search(TrieNode* const root, const std::string& query)
{
    TrieNode* curr = root;

    for (auto c : query) {
        const int idx = c - 'a';
        if (!curr->children[idx]) {
            return 0;
        }
        curr = curr->children[idx];
    }
    return curr->count;
}

/**
 * More complex solution using Tries
 * @param strList: Array with strings
 * @param queries: Array with queries
 * @return Array with the number of instances of each query
 */
std::vector<int> matchingStrings(const std::vector<std::string>& strList,
                                 const std::vector<std::string>& queries)
{
    TrieNode* root = new TrieNode();

    for (auto str : strList) {
        insert(root, str);
    }

    std::vector<int> res;
    res.reserve(queries.size());

    for (auto query : queries) {
        res.push_back(search(root, query));
    }

    delete root;
    return res;
}

/**
 * Simpler solution using Hash tables
 * @param strList: Array with strings
 * @param queries: Array with queries
 * @return Array with the number of instances of each query
 */
std::vector<int> matchingStrings(const std::vector<std::string>& stringList,
                                 const std::vector<std::string>& queries)
{
    std::map<std::string, int> freq;

    for (std::string str : stringList) {
        freq[str]++;
    }

    std::vector<int> result;
    result.reserve(queries.size());

    for(std::string query : queries) {
        result.push_back(freq[query]);
    }

    return result;
}
