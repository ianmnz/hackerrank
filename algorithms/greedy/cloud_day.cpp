/**
 * https://www.hackerrank.com/challenges/cloudy-day/problem
 */

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>


struct CloudOrTown
{
    enum Type {
        CLOUD_BEGIN = -1,
        TOWN = 0,
        CLOUD_END = 1
    };

    CloudOrTown(long x, Type t, int i, long p) : pos(x), type(t), index(i), pop(p) {}

    /**
     * We order them by cloud_begin < town < cloud_end
     */
    bool operator<(const CloudOrTown& other)
    {
        if (pos == other.pos) {
            return type < other.type;

        } else {
            return pos < other.pos;
        }
    }

    long pos;
    Type type;
    int index;
    long pop;
};


/**
 * @param town_pop: Array with towns' populations
 * @param town_loc: Array with towns' locations
 * @param cloud_loc: Array with clouds' locations
 * @param cloud_range: Array with clouds' coverage range
 * @return The maximum of the population that will be in a sunny town by removing one cloud
 */
long maximumPeople(const std::vector<long>& town_pop,
                   const std::vector<long>& town_loc,
                   const std::vector<long>& cloud_loc,
                   const std::vector<long>& cloud_range)
{
    const int n = town_loc.size();
    const int m = cloud_loc.size();

    std::vector<CloudOrTown> cloudsAndTowns;

    for (int i = 0; i < n; ++i) {
        cloudsAndTowns.push_back(CloudOrTown(town_loc[i], CloudOrTown::Type::TOWN, i, town_pop[i]));
    }

    for (int j = 0; j < m; ++j) {
        cloudsAndTowns.push_back(CloudOrTown(cloud_loc[j] - cloud_range[j], CloudOrTown::Type::CLOUD_BEGIN, j, -1));
        cloudsAndTowns.push_back(CloudOrTown(cloud_loc[j] + cloud_range[j],  CloudOrTown::Type::CLOUD_END, j, -1));
    }

    std::sort(cloudsAndTowns.begin(), cloudsAndTowns.end());

    long sunny = 0;
    std::set<int> coverage;
    std::map<int, long> cloud_removal_gain;
    long max_cloud_removal_gain = 0;

    for (const auto& cloudOrTown : cloudsAndTowns) {
        if (cloudOrTown.type == CloudOrTown::Type::CLOUD_BEGIN) {
            coverage.insert(cloudOrTown.index);

        } else if (cloudOrTown.type == CloudOrTown::Type::CLOUD_END) {
            coverage.erase(cloudOrTown.index);

        } else {
            if (coverage.empty()) {
                // There are no clouds covering the town => sunny town
                sunny += cloudOrTown.pop;

            } else if (coverage.size() == 1) {
                // There is exactly only one cloud covering it
                // We compute its gain and check if it maximises it
                const int index = *coverage.begin();
                cloud_removal_gain[index] += cloudOrTown.pop;
                max_cloud_removal_gain = std::max(max_cloud_removal_gain, cloud_removal_gain[index]);
            }
        }
    }

    return sunny + max_cloud_removal_gain;
}


int main()
{
    const std::vector<long> town_pop {10, 100};
    const std::vector<long> town_loc { 5, 100};
    const std::vector<long> cloud_loc   {4};
    const std::vector<long> cloud_range {1};

    std::cout << maximumPeople(town_pop, town_loc, cloud_loc, cloud_range) << std::endl;    // Expected output: 110

    return 0;
}
