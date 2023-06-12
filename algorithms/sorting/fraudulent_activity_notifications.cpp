/**
 * https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
 */

#include <iostream>
#include <vector>
#include <algorithm>


/**
 * @param expenditures: Array with expenditures in chronological order
 * @param d: The moving window size
 * @return The number of notifications sent
 */
int activityNotifications(const std::vector<int>& expenditures, const int d)
{
    const int n = expenditures.size();

    if (n <= d) {
        return 0;
    }

    // Since d is fixed, we compute the indices for the median just once
    // If d is odd, we compute twice the same value floor(d/2)
    const int left = d % 2 == 0 ? d/2 - 1 : d/2;
    const int right = d/2;

    int notifications = 0;

    // We initially sort the trailing vector so we can query for the median
    // using the indices left and right above
    std::vector<int> trail(expenditures.cbegin(), expenditures.cbegin() + d);
    std::sort(trail.begin(), trail.end());

    int expenditure, median_doubled;
    for (int i = d; i < n; ++i) {
        median_doubled = trail[left] + trail[right];
        expenditure = expenditures[i];

        // Since we would divide the median by 2 and then multiply it by 2
        // we avoid superfluous operations by just comparing to the doubled median
        if (expenditure >= median_doubled) {
            ++notifications;
        }

        // Remove oldest expenditure
        // Since the vector is sorted, we use lower_bound to do a binary search
        trail.erase(std::lower_bound(trail.cbegin(), trail.cend(), expenditures[i - d]));

        // Insert current expenditure in correct place
        // Since the vector is sorted, we use upper_bound to do a binary search
        trail.insert(std::upper_bound(trail.cbegin(), trail.cend(), expenditure), expenditure);
    }

    return notifications;
}


int main()
{
    const int d = 5;
    const std::vector<int> arr { 2, 3, 4, 2, 3, 6, 8, 4, 5 };

    std::cout << activityNotifications(arr, d) << std::endl;    // Expected output: 2

    return 0;
}
