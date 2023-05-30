/**
 * https://www.hackerrank.com/challenges/counter-game/problem
 */

#include <iostream>


bool counterGame(long n)
{
    if (n == 1l) {
        return false;
    }

    // If n is a power of 2, the game
    // consists of counting the number
    // of trailing zeros in binary representation.

    // Otherwise, it consists of removing
    // all leading 1's until n is power of 2

    // In the end, the idea is to count all
    // leading 1's and all trailing 0's.

    // By subtracting 1 from n, we flip all trailing
    // 0's (and eventually last 1 if n was odd), and
    // now we just have to count the number of 1's
    n -= 1l;

    // Counts the number of non-zero bits iteratively
    // by removing at each iteration the trailing 1
    // When becomes n a power of 2, it has only one 1
    // and so the next iteration brings it to zero.
    // _popcount64 would give the same result
    // but with O(1) (apparently)
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }

    // If count is odd, Louise wins
    // Otherwise Richard wins
    return (count & 1);
}

int main()
{
    long n = 15l;
    std::cout << counterGame(n) << std::endl; // Expected output: true

    return 0;
}
