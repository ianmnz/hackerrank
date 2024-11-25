/**
 * https://www.hackerrank.com/challenges/truck-tour/problem
 */

#include <iostream>
#include <queue>
#include <vector>


struct Pump
{
    int amount;
    int distance_to_next;
};

/**
 * @param pumps Array with pump objects
 * @param start The starting point of the array
 * @return The start offset value
 */
int get_start_offset(const std::vector<Pump> &pumps, const int start)
{
    const int n = pumps.size();
    long tank = 0;

    for (int offset = 0; offset < n; ++offset) {
        // We circle around the pumps vector
        // we could use a circular queue as well
        const Pump &pump = pumps[(start + offset) % n];
        tank += (long)(pump.amount - pump.distance_to_next);

        if (tank < 0) {
            // We start next check from the next pump
            // since all pumps before would yield an
            // equivalent result with negative tank value
            return offset + 1;
        }
    }

    // In this case, we found a valid starting point
    // so no offset is required
    return 0;
}

/**
 * @param pumps Array of pump objects
 * @return The starting point
 */
int truckTour(const std::vector<Pump> &pumps)
{
    const int n = pumps.size();
    int start = 0;

    int offset;
    do {
        // We offset the start by chunks to avoid
        // re-checking invalid starting points.
        // This optimization (+= offset vs += 1) allows
        // for linear complexity since we'll check each
        // pump at most twice
        offset = get_start_offset(pumps, start);
        start = (start + offset) % n;

    } while (offset > 0);

    return start;
}


int main(int argc, char const *argv[])
{
    std::vector<Pump> pumps{{1, 5}, {10, 3}, {3, 4}};
    std::cout << truckTour(pumps) << std::endl;  // Expected output: 1

    return 0;
}
