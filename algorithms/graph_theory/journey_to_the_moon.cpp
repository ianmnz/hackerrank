/*
 * https://www.hackerrank.com/challenges/journey-to-the-moon/problem
 */

#include <iostream>
#include <vector>
#include <map>
#include <numeric>

using ll = long long;

/*
 * Disjoint sets algorithm : find
 * @param parent: Parent vector
 * @param i: Node to find the root
 * @return: i's root node
 */
int find(std::vector<int>& parent, const int i)
{
    if (parent[i] == i) {
        return i;
    } else {
        parent[i] = find(parent, parent[i]);
        return parent[i];
    }
}

/*
 * Disjoint sets algorithm : union
 * @param parent: Parent vector
 * @param i: Left node
 * @param j: Right node
 */
void unite(std::vector<int>& parent, const int i, const int j)
{
    int parent_i = find(parent, i);
    int parent_j = find(parent, j);

    if (parent_i != parent_j) {
        parent[parent_i] = parent_j;
    }
}

/*
 * @param n: Number of astronauts
 * @param astronaut: Array containing on the i-th element the ID of astronauts of the same country
 * @return: Number of valid pairs
 */
ll journeyToMoon(int n, std::vector<std::vector<int>> astronaut)
{
    std::vector<int> parent(n);
    std::iota(parent.begin(), parent.end(), 0);

    // Find all countries
    for (auto vec : astronaut) {
        unite(parent, vec[0], vec[1]);
    }

    std::map<int, ll> count;

    // And the number of astronauts belonging to each
    for (int i = 0; i < n; ++i) {
        count[find(parent, i)] += 1ll;
    }

    // All combinations of astronauts from the same country
    // that is, all edges between same country astronauts:
    ll same_country_pair = 0ll;
    for (auto country : count) {
        same_country_pair += country.second * country.second;
    }

    // Combinatroics to find the numbers of pairs
    // nC2 - \sum((#country_size)C2)
    return ((ll)n * (ll) n - same_country_pair) / 2ll;
}

int main()
{
    const int n = 5;
    std::vector<std::vector<int>> astronaut {{0, 1}, {2, 3}, {0, 4}};
    const ll nb_pairs = journeyToMoon(n, astronaut);

    std::cout << nb_pairs << std::endl; // Expected output: 6

    return 0;
}
