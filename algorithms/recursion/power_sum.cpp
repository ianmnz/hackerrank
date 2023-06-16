/**
 * https://www.hackerrank.com/challenges/the-power-sum/problem
 */

#include <iostream>
#include <vector>


/**
 * @param b: Base
 * @param n: Exponent
 * @return The nth power b**n
 */
int nth_power(const int b, const int n)
{
    if (n == 0 || b == 1) {
        return 1;

    } else if (n == 1) {
        return b;

    } else if (n % 2 == 0) {
        const int pow = nth_power(b, n/2);
        return pow * pow;

    } else {
        return b * nth_power(b, n - 1);
    }
}

/**
 * @param powers: Array with candidates in the form i**N
 * @param start: Starting index of the array
 * @param target: The target value
 * @return The number of combinations that yields the target value
 */
int combinations(const std::vector<int>& powers, const int start, const int target)
{
    int count = 0;
    for (int i = start; i < powers.size(); ++i) {
        const int remainder = target - powers[i];

        if (remainder <= 0) {
            if (remainder == 0) ++count;
            break;
        }

        count += combinations(powers, i + 1, remainder);
    }

    return count;
}

/**
 * @param X: The target value
 * @param N: The power of the values
 * @return The number of combinations that yields the target value
 */
int powerSum(const int X, const int N)
{
    std::vector<int> powers;
    int b = 1, pow = 1;

    while (pow <= X) {
        powers.push_back(pow);
        ++b;
        pow = nth_power(b, N);
    }

    return combinations(powers, 0, X);
}


int main()
{
    const int X = 100, N = 2;

    std::cout << powerSum(100, 2) << std::endl; // Expected output: 3

    return 0;
}
