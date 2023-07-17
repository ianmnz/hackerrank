/**
 * https://www.hackerrank.com/challenges/countingsort4/problem
 */

#include <iostream>
#include <vector>
#include <string>


/**
 * @param arr : Array of pairs of strings, where the first is the counting index, and the second is the string itself
 */
void countSort(const std::vector<std::vector<std::string>>& arr)
{
    const int n = arr.size();

    std::vector<std::vector<std::string>> count(n);

    // The first half becomes a hyphen "-"
    for (int i = 0; i < n/2; ++i) {
        const int idx = std::stoi(arr[i][0]);
        count[idx].push_back("-");
    }

    for (int i = n/2; i < n; ++i) {
        const int idx = std::stoi(arr[i][0]);
        count[idx].push_back(arr[i][1]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < count[i].size(); ++j) {
            std::cout << count[i][j] << " ";
        }
    }
}


int main()
{
    const std::vector<std::vector<std::string>> arr {{"1", "e"}, {"2", "a"}, {"1", "b"}, {"3", "a"}, {"4", "f"},
                                                     {"1", "f"}, {"2", "a"}, {"1", "e"}, {"1", "b"}, {"1", "c"}};

    countSort(arr); // Expected output: - - f e b c - a - -

    return 0;
}
