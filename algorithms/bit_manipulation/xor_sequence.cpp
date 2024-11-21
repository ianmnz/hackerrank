/**
 * https://www.hackerrank.com/challenges/xor-se/problem
 */

#include <iostream>


/**
 * @param x An index of the array A_x
 * @return The accumulate xor-sum of A_0 ^ A_1 ^ ... ^ A_x
 */
long xorUpTo(const long x)
{
    // Cycles in periods of 8
    const int r = x % 8;

    if (r <= 1)      return x;
    else if (r <= 3) return 2;
    else if (r <= 5) return x + 2;
    else             return 0l;
}

/**
 * @param l Left side of the interval
 * @param r Right side of the interval
 * @return The accumulate xor-sum of A_l ^ A_(l+1) ^ ... ^ A_r
 */
long xorSequence(const long l, const long r)
{
    /*
    (A_0 ^ ... ^ A_l-1) ^ (A_0 ^             ...           ^ A_r) =
    (A_0 ^ ... ^ A_l-1) ^ (A_0 ^ ... ^ A_l-1  ^  A_l ^ ... ^ A_r) =
    (A_0 ^ ... ^ A_l-1) ^ (A_0 ^ ... ^ A_l-1) ^ (A_l ^ ... ^ A_r) =
                        0                     ^ (A_l ^ ... ^ A_r) =
                                                (A_l ^ ... ^ A_r)
    */
    return xorUpTo(l - 1l) ^ xorUpTo(r);
}


int main()
{
    const long l = 15l, r = 20l;
    std::cout << xorSequence(l, r) << std::endl; // Expected: 22

    return 0;
}
