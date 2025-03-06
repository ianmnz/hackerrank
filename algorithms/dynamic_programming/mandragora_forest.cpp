/**
 * https://www.hackerrank.com/challenges/gridland-metro/problem
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

/**
 * @param H Array with the health value of each mandragora
 * @return The max XP possible
 */
long mandragora(std::vector<int> &H)
{
    // We sort the array to be able to choose a partition
    // point where eating another mandragora reduces
    // the obtained XP
    std::sort(H.begin(), H.end());

    long tail_sum = std::accumulate(H.cbegin(), H.cend(), 0l);

    for (int i = 0; i < H.size(); ++i) {
        const int s = i + 1;

        // Either eat [0, i] and battle (i, n - 1]
        //     Or eat [0, i) and battle [i, n - 1]
        const long eat_i = (s + 1) * (tail_sum - H[i]);
        const long bat_i = s * tail_sum;

        // Since the function has a maximum,
        // we choose the partition index i where
        // eating is not worth it anymore
        if (bat_i >= eat_i) {
            return bat_i;
        }

        tail_sum -= H[i];
    }

    return tail_sum;
}


int main()
{
    std::vector<int> H {5, 2, 6, 11, 29, 12, 7};
    std::cout << mandragora(H) << std::endl;  // Expected output: 260

    return 0;
}
