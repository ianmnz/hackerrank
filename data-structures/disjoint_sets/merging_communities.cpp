/**
 * https://www.hackerrank.com/challenges/merging-communities/problem
 */

#include <iostream>
#include <vector>
#include <numeric>


class SocialNetwork
{
public:
    SocialNetwork(const int N)
    {
        community.resize(N);
        std::iota(community.begin(), community.end(), 0);
        sizes = std::vector<int>(N, 1);
    }

    void merge(const int lcomm, const int rcomm)
    {
        unite(lcomm - 1, rcomm - 1);
    }

    int size_of(const int comm)
    {
        const int idx = find(comm - 1);
        return sizes[idx];
    }

private:
    int find(const int idx)
    {
        if (community[idx] == idx) {
            return idx;
        }
        const int comm = find(community[idx]);
        community[idx] = comm;
        return comm;
    }

    void unite(const int lhs, const int rhs)
    {
        const int lcomm = find(lhs);
        const int rcomm = find(rhs);

        if (lcomm == rcomm) {
            return;
        }

        const int lsize = sizes[lcomm];
        const int rsize = sizes[rcomm];

        if (lsize <= rsize) {
            community[lcomm] = rcomm;
            sizes[rcomm] += sizes[lcomm];
            sizes[lcomm] = 0;

        } else {
            community[rcomm] = lcomm;
            sizes[lcomm] += sizes[rcomm];
            sizes[rcomm] = 0;
        }
    }

    std::vector<int> community;
    std::vector<int> sizes;
};


int main()
{
    const int N = 3;
    SocialNetwork social_network(N);

    social_network.merge(1, 2);
    social_network.merge(2, 3);

    std::cout << (social_network.size_of(2) == social_network.size_of(3)) << std::endl;  // Expected output: true

    return 0;
}
