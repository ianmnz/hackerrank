/**
 * https://www.hackerrank.com/challenges/the-great-xor/problem
 */

#include <iostream>

/**
 * @param x Long integer
 * @return Nb of integers such as x ^ a > x
 */
long theGreatXor1(long x)
{
    long res = 0l;
    int n = 0;

    do {
        res += !(x & 1) * (1l << n++);
    } while (x >>= 1);

    return res;
}

/**
 * @brief Second version
 *
 * @param x Long integer
 * @return Nb of integers such as x ^ a > x
 */
long theGreatXor2(const long x)
{
    int msb = 0;
    while (x >> msb) {
        msb++;
    }
    return (1l << msb) - 1l - x;
}

int main()
{
    constexpr long x = 100l;
    std::cout << theGreatXor2(x) << std::endl;  // Expected output: 27

    return 0;
}
