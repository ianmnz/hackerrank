/**
 * https://www.hackerrank.com/challenges/and-product/problem
 */

#include <iostream>
#include <cmath>

/**
 * Naive time-outed solution
 * @param a: Smaller value
 * @param b: Bigger value
 * @return The product a & (a + 1) & ... & b
*/
long andProduct(const long a, const long b)
{
    if (!a || a == b) {
        return a;
    }

    long res = a;
    for (int i = a + 1; i <= b; ++i) {
        res &= i;
    }
    return res;
}


/**
 * Efficient solution
 * @param a: Smaller value
 * @param b: Bigger value
 * @return The product a & (a + 1) & ... & b
*/
long andProduct(long a,long b)
{
    if(!a){
        return 0;
    }

    // We will try to find the same leading bits
    // to use the idea of most significant bits
    // If they have the same leading bits, than that's
    // the answer
    int shift = 0;
    while(a != b){
        a >>= 1;
        b >>= 1;
        shift++;
    }
    return a << shift;
}


/**
 * Cleaner solution
 * @param a: Smaller value
 * @param b: Bigger value
 * @return The product a & (a + 1) & ... & b
*/
long andProduct(const long a, long b)
{
    if (!a || a == b) {
        return a;
    }

    // As before, we will use the idea of the leading bits
    // to take into account the most signicant bits
    // At each iteration, we toggle the rightmost bit
    // We b <= a, it means we found the corresponding leading bits
    while (b > a) {
        b &= (b - 1);
    }
    return b;
}


int main()
{
    const long a = 12;
    long b = 15;

    std::cout << andProduct(a, b) << std::endl; // Expected output: 12

    return 0;
}
