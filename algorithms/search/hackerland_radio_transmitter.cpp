/**
 * https://www.hackerrank.com/challenges/hackerland-radio-transmitters/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>


/**
 * @param x : Array of city locations
 * @param k : Coverage area
 * @return The minimum amount of antennae
 */
int hackerlandRadioTransmitters(std::vector<int>& x, const int k)
{
    const int n = x.size();

    std::sort(x.begin(), x.end());

    // We consider initially that all cities have an antenna
    int nb_antennae = n;

    int leftmost_covered = x[0];
    int last_antenna = x[0];

    // We eliminate an antenna every time a new one
    // covers the leftmost one or one antenna to the
    // right is already covered
    for (int i = 1; i < n; ++i) {
        if (x[i] - k <= leftmost_covered) {
            nb_antennae--;
            last_antenna = x[i];

        } else if (x[i] <= last_antenna + k){
            nb_antennae--;

        } else {
            leftmost_covered = x[i];
            last_antenna = x[i];
        }
    }

    return nb_antennae;
}


int main()
{
    const int k = 2;
    std::vector<int> x = {7, 2, 4, 6, 5, 9, 12, 11};

    std::cout << hackerlandRadioTransmitters(x, k) << std::endl;    // Expected output: 3

    return 0;
}
