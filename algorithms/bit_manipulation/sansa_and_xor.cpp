/**
 * https://www.hackerrank.com/challenges/sansa-and-xor/problem
 */

#include <iostream>
#include <vector>


/**
 * @param arr: Array of numbers
 * @return The accumulative XOR for all subarrays
*/
int sansaXor(const std::vector<int>& arr)
{
    const int n = arr.size();

    if (n % 2 == 0) {
        return 0;
    }

    int res = arr[0];
    for (int i = 2; i < n; i += 2) {
        res ^= arr[i];
    }
    return res;
}


int main()
{
    std::vector<int> arr = {4, 5, 7, 5};
    std::cout << sansaXor(arr) << std::endl;  // Expected output: 0

    return 0;
}
