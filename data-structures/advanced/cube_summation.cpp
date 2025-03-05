/**
 * https://www.hackerrank.com/challenges/cube-summation/problem
 */

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief A string split function provided by Hackerrank.
 * I was feeling lazy so I neither wrote it nor copied it
 */
std::vector<std::string> split(const std::string &);


struct Index {
    int x;
    int y;
    int z;
};

/**
 * @param n The dimension size of the n x n x n matrix
 * @param operations A vector with updates and queries
 * @return An array with the results of each query
 */
std::vector<long> cubeSum(const int n, const std::vector<std::string> &operations)
{
    std::vector<int> matrix(n * n * n, 0);

    auto update = [n, &matrix](const Index &idx, const int W) {
        matrix[(idx.z - 1) + n * (idx.y - 1) + n * n * (idx.x - 1)] = W;
    };

    auto query = [n, &matrix](const Index &from, const Index &to) {
        long sum = 0l;
        for (int i = from.x - 1; i < to.x; ++i) {
            for (int j = from.y - 1; j < to.y; ++j) {
                for (int k = from.z - 1; k < to.z; ++k) {
                    sum += matrix[k + n * j + n * n * i];
                }
            }
        }
        return sum;
    };

    std::vector<long> queries;
    queries.reserve(operations.size());

    for (auto &op : operations) {
        const auto tokens = split(op);

        std::vector<int> values(tokens.size() - 1);
        std::transform(
            tokens.cbegin() + 1, tokens.cend(), values.begin(),
            [](const std::string &token) { return std::stoi(token); });

        if (tokens[0] == "UPDATE") {
            const Index idx = {values[0], values[1], values[2]};
            const int W = values[3];
            update(idx, W);

        } else if (tokens[0] == "QUERY") {
            const Index from = {values[0], values[1], values[2]};
            const Index to = {values[3], values[4], values[5]};
            queries.push_back(query(from, to));
        }
    }

    queries.shrink_to_fit();
    return queries;
}


int main()
{
    const int n = 4;
    const std::vector<std::string> operations {
        "UPDATE 2 2 2 4",
        "QUERY 1 1 1 3 3 3",
        "UPDATE 1 1 1 23",
        "QUERY 2 2 2 4 4 4",
        "QUERY 1 1 1 3 3 3"
    };

    for (auto res : cubeSum(n, operations)) {
        std::cout << res << " ";    // Expected output: 4 4 27
    }
    std::cout << std::endl;

    return 0;
}
