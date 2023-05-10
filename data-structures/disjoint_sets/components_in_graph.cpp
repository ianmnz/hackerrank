/*
 * https://www.hackerrank.com/challenges/components-in-graph/problem
 */

#include <iostream>
#include <vector>


int find(std::vector<int>& arr, const int n)
{
    if (arr[n] < 0) {
        return n;

    } else {
        arr[n] = find(arr, arr[n]);
        return arr[n];
    }
}

// Slightly modified Disjoint Set algorithm to
// count the number of nodes belonging to the same
// root node
void unite(std::vector<int>& arr, const int n1, const int n2)
{
    const int root1 = find(arr, n1);
    const int root2 = find(arr, n2);

    if (root1 != root2) {
        arr[root1] += arr[root2];
        arr[root2] = root1;
    }
}

std::vector<int> componentsInGraph(const std::vector<std::vector<int>>& gb)
{
    // We count the number of nodes N in the graph
    // assuming that N is the number of the biggest
    // node in the vector gb
    int n = 0;
    for (const auto& edge : gb) {
        const int n1 = edge[0];
        const int n2 = edge[1];

        n = std::max(n, std::max(n1, n2));
    }

    std::vector<int> arr(n, -1);

    for (const auto& edge : gb) {
        const int n1 = edge[0];
        const int n2 = edge[1];

        unite(arr, n1 - 1, n2 - 1);
    }

    int largest = n, smallest = -n;
    for (const auto size : arr) {

        if (size >= -1) {
            continue;
        }

        if (size < largest) {
            largest = size;
        }

        if (size > smallest) {
            smallest = size;
        }
    }

    return {std::abs(smallest), std::abs(largest)};
}


int main()
{
    const std::vector<std::vector<int>> gb {{1, 6}, {2, 7}, {3, 8}, {4, 9}, {2, 6}};
    const std::vector<int> result = componentsInGraph(gb);

    std::cout << result[0] << ", " << result[1] << std::endl;   // Expected output: 2, 4

    return 0;
}
