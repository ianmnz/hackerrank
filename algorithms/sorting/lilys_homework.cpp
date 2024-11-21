/**
 * https://www.hackerrank.com/challenges/lilys-homework/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


/**
 * @param arr Array to be sorted
 * @param sorted Reference sorted array
 * @return the minimum number of swaps necessary to go from array to sorted
 */
int get_swap_distance(std::vector<int> arr, const std::vector<int> &sorted)
{
    std::map<int, size_t> target;
    for (int i = 0; i< sorted.size(); ++i) {
        target[sorted[i]] = i;
    }

    int nb_swaps = 0;
    for (int i = 0; i < arr.size(); ++i) {
        int curr = arr[i];

        while (i != target[curr]) {
            std::swap(arr[target[curr]], arr[i]);
            curr = arr[i];
            nb_swaps++;
        }
    }
    return nb_swaps;
}

/**
 * @param arr Array to be sorted
 * @return The minimum number of necessary swaps to sort the array
 */
int lilysHomework(const std::vector<int> &arr)
{
    std::vector<int> ascending(arr);

    std::sort(ascending.begin(), ascending.end());

    std::vector<int> descending(ascending.rbegin(), ascending.rend());

    const int dist_asc = get_swap_distance(arr, ascending);
    const int dist_des = get_swap_distance(arr, descending);

    return std::min(dist_asc, dist_des);
}


int main()
{
    std::vector<int> arr {3, 4, 2, 5, 1};

    std::cout << lilysHomework(arr) << std::endl; // Expected : 2

    return 0;
}
