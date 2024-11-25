/**
 * https://www.hackerrank.com/challenges/minimum-average-waiting-time/problem
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>


struct Customer
{
    int order;
    int cook;

    bool operator<(const Customer &other) const
    {
        return this->order < other.order;
    }
};

/**
 * @param customers Array of customers
 * @return The minimum waiting average
 */
long minimumAverage(std::vector<Customer> &customers)
{
    const int n = customers.size();
    sort(customers.begin(), customers.end());

    auto comp = [](const Customer &lhs, const Customer &rhs) {
        return lhs.cook > rhs.cook;
    };
    std::priority_queue<Customer, std::vector<Customer>, decltype(comp)> waiting(comp);

    int idx = 0;
    long time = 0, wait_time = 0;

    // While there are customers to order
    // or customers who are waiting
    while (idx < n || !waiting.empty()) {

        // Customer ordered and is now waiting
        while (idx < n && time >= customers[idx].order) {
            waiting.push(customers[idx++]);
        }

        // No customer waiting, take next order
        if (waiting.empty()) {
            time = customers[idx].order;
            continue;
        }

        // Serve order by poping from waiting heap
        Customer customer = waiting.top();
        waiting.pop();

        time += customer.cook;
        wait_time += time - customer.order;
    }

    return wait_time / n;
}


int main(int argc, char const *argv[])
{
    std::vector<Customer> customers {{0, 3}, {1, 9}, {2, 5}};
    std::cout << minimumAverage(customers) <<  std::endl;  // Expected output: 8

    return 0;
}
