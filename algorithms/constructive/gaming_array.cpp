/**
 * https://www.hackerrank.com/challenges/an-interesting-game-1/problem
 */

#include <iostream>
#include <vector>
#include <set>


/**
 * @param arr: Array with distinct values
 * @return The winner. True for Andy, false for Bob.
*/
bool gamingArray(const std::vector<int>& arr)
{
    const int n = arr.size();

    if (n == 1) {
        return false;
    }

    using valIdx_t = std::pair<int, int>;

    auto comparator = [](const valIdx_t& lhs, const valIdx_t& rhs) { return lhs.first > rhs.first; };
    std::set<valIdx_t, decltype(comparator)> maximum_indices(comparator);

    // We iterate over arr to find all values and their indices
    // sorting then in a set by decreasing order
    for (int i = 0; i < n; ++i) {
        maximum_indices.insert(std::make_pair(arr[i], i));
    }

    // We keep track of the last removed index
    // as well as the player that dit it
    bool winner = true;
    int last_removed_index = n;

    // We then iterate over the sorted set and update the last_removed_index
    // We stop either when we reach the end of the set or if the first element
    // of the array was removed
    std::set<valIdx_t, decltype(comparator)>::const_iterator it;
    for (it = maximum_indices.cbegin(); it != maximum_indices.cend(); ++it) {
        if (it->second < last_removed_index) {
            last_removed_index = it->second;
            winner = !winner;
        }

        if (last_removed_index <= 0) {
            break;
        }
    }

    return winner;
}


/**
 * Alternative simpler version of the function gaminArray
 * @param arr: Array with distinct values
 * @return The winner. True for Andy, false for Bob.
*/
bool gamingArray2(const std::vector<int>& arr)
{
    // We iterate once and keep track of every time
    // we found a number in arr bigger than all of the
    // previous ones
    bool winner = true;
    int prev = 0;
    for(auto &num : arr) {
        if(num > prev) {
            prev = num;
            winner = !winner;
        }
    }
    return winner;
}


int main()
{
    const std::vector<int> arr = {2, 3, 5, 4, 1};

    std::cout << gamingArray(arr) << std::endl; // Expected output: false

    return 0;
}
