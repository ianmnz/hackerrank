/*
 * https://www.hackerrank.com/challenges/pylons/problem
 */

#include <iostream>
#include <vector>


int pylons(const int k, const std::vector<int> &arr)
{
    int nb_built = 0;

    const int cover_band = k - 1;
    const int n = arr.size();

    int candidate = cover_band;
    int last_covered = -1;

    // We will try to cover the biggest area possible
    // by looking directly to the furthest candidate possible
    // if it's not available, we will look the previous
    // candidate and so on down to the last covered area
    while (last_covered < n - 1)
    {
        if (arr[candidate])
        {
            nb_built++;
            last_covered = candidate + cover_band;
            candidate += 1 + 2 * cover_band;
            candidate = std::min(candidate, n - 1); // To keep it inside the vector's limits
        }
        else
        {
            candidate--;
            if (candidate < 0 || candidate <= last_covered - cover_band)
            {
                // Outside the vector or already at a covered area
                return -1;
            }
        }
    }

    return nb_built;
}


int main()
{
    const int k = 2;
    const std::vector<int> arr{0, 1, 1, 1, 1, 0};

    std::cout << pylons(k, arr) << std::endl; // Expected output: 2

    return 0;
}
