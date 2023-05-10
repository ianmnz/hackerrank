/*
 * https://www.hackerrank.com/challenges/organizing-containers-of-balls/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>

/*
 * @param container: Array of containers with the initial distribution of different types of balls
 * @return: boolean if is possible to rearrange each conatiner with only one type of ball
 */
bool organizingContainers(std::vector<std::vector<int>> container)
{
    const int n = container.size();

    // We first count the total number of balls per type
    // and the total capacity of each container
    // The capacity is invariant since a swap doesn't
    // increase the number of balls on each container
    std::vector<int> balls_per_type(n, 0);
    std::vector<int> containers_cap(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            containers_cap[i] += container[i][j];
            balls_per_type[j] += container[i][j];
        }
    }

    std::sort(containers_cap.begin(), containers_cap.end());
    std::sort(balls_per_type.begin(), balls_per_type.end());

    // Finally, we check to see if we will be able to
    // allocate all ball types in a unique conatiner
    for (int i = 0; i < n; ++i) {
        if (containers_cap[i] != balls_per_type[i]) {
            return false;
        }
    }

    return true;
}


int main() {

    std::vector<std::vector<int>> container {{1, 4}, {2, 3}};
    std::cout << std::boolalpha << organizingContainers(container) << std::endl;    // Expected output : false
    return 0;
}
