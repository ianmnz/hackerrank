/**
 * https://www.hackerrank.com/challenges/bonetrousle/problem
 */

#include <iostream>
#include <vector>


/**
 * @param n: The total spaghetti
 * @param k: The max available stick box
 * @param b: The number of boxes
 * @return Array with the stick boxes
 */
std::vector<long> bonetrousle(const long n, const long k, const long b)
{
    unsigned long lower;    // b + (b - 1) + ... + 2 + 1
    unsigned long upper;    // k + (k - 1) + ... + (k - b + 1)

    // To avoid overflows when k~10^18 and b~10^5
    // we have to be careful with the multiplication
    // of the upper bound
    if (b & 1) {
        // b is odd
        lower = b * ((b + 1l) / 2l);
        upper = b * ((2l * k - b + 1l) / 2l);
    } else {
        // b is even
        lower = (b / 2l) * (b + 1l);
        upper = (b / 2l) * (2l * k - b + 1l);
    }

    if (n < lower || upper < n) {
        // Neither enough sticks to buy in b boxes
        // n > k + (k - 1) + (k - 2) + ... + (k - b + 1)
        // Nor spaghetti big enough for b boxes
        // n < b + (b - 1) + (b - 2) + ... + 1
        return { -1l };
    }

    std::vector<long> boxes(b);

    const long q = (n - lower) / b;     // Common increment
    const long r = (n - lower) - q * b; // The remainder

    for (int i = 0; i < b; ++i) {
        boxes[i] = (1l + i) + q;
    }

    for (int i = b - r; 0 <= i && i < b; ++i) {
        boxes[i]++;
    }

    return boxes;
}


int main()
{
    const long n = 12, k = 8, b = 3;
    const std::vector<long> result = bonetrousle(n, k, b);

    for (const auto val : result) {
        std::cout << val << " ";    // Expected output: 3 4 5
    }
    std::cout << std::endl;

    return 0;
}
