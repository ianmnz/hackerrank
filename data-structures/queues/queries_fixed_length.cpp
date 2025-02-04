#include <deque>
#include <iostream>
#include <vector>


std::vector<int> solve(const std::vector<int> &arr,
                       const std::vector<int> &queries)
{
    std::vector<int> res;
    res.reserve(queries.size());

    const int n = arr.size();

    for (const int d : queries) {
        std::deque<int> q;
        int minimum = std::numeric_limits<int>::max();

        for (int j = 0; j < n; ++j) {

            // q is in decreasing order
            while (!q.empty() && q.back() < arr[j]) {
                q.pop_back();
            }
            q.push_back(arr[j]);

            if (j + 1 < d) {
                continue;
            }

            if (minimum > q[0]) {
                minimum = q[0];
            }

            if (q[0] == arr[j - d + 1]) {
                q.pop_front();
            }
        }

        res.push_back(minimum);
    }

    return res;
}


int main(int argc, char const *argv[])
{
    const std::vector<int> arr{33, 11, 44, 11, 55};
    const std::vector<int> queries{1, 2, 3, 4, 5};

    const auto res = solve(arr, queries);
    for (int min_i : res) {
        std::cout << min_i << " ";
    }
    std::cout << std::endl;  // Expected output: 11 33 44 44 55

    return 0;
}
