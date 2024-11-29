/**
 * https://www.hackerrank.com/challenges/bob-and-ben/problem
 */

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>


struct Tree
{
    int m;
    int k;
};

/**
 * I must say I don't fully understand the solution
 * but it is based on Nim-games and Grundy numbers.
 *
 * https://www.geeksforgeeks.org/combinatorial-game-theory-set-4-sprague-grundy-theorem/
 * https://en.wikipedia.org/wiki/Sprague%E2%80%93Grundy_theorem
 *
 * @param trees The game's forest
 * @return true if Bob wins
 * @return false if Ben wins
 */
bool bobAndBen(const std::vector<Tree> &trees)
{
    std::vector<int> grundy_numbers;
    grundy_numbers.reserve(trees.size());

    for (const auto &tree : trees) {
        if (tree.m != 0 && tree.m != 2) {
            grundy_numbers.push_back((tree.m) % 2 + 1);
        }
    }

    const int nim_sum = std::accumulate(
        grundy_numbers.cbegin(), grundy_numbers.cend(), 0, std::bit_xor<>());

    return nim_sum != 0;
}


int main()
{
    const std::vector<Tree> trees{{1, 2}, {1, 3}, {3, 2}};

    std::cout << std::boolalpha << bobAndBen(trees) << std::endl;  // Expected : true

    return 0;
}
