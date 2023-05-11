/*
 * https://www.hackerrank.com/challenges/fibonacci-modified/problem
 */

#include <iostream>
#include <vector>


/*
 * @param i: Index of the value to compute
 * @param fibs: Array stocking previously computed values
 * @return Fib_i
 */
int fib(const int i, std::vector<long long>& fibs)
{
    if (fibs[i] >= 0) {
        // If already in memory, use Fibs_i value
        return fibs[i];

    } else {
        const int t_i_2 = fib(i - 2, fibs);
        const int t_i_1 = fib(i - 1, fibs);

        // Otherwise, compute and stock it
        fibs[i] = t_i_2 + t_i_1 * t_i_1;
        return fibs[i];
    }
}

/*
 * @param t1: Initial Fib value, F_0
 * @param t2: Initial Fib value, F_1
 * @param n: Fibonacci number to check, F_n
 * @return F_n
 */
int fibonacciModified(const int t1, const int t2, const int n)
{
    std::vector<long long> fibs (n, -1);

    fibs[0] = t1;
    fibs[1] = t2;

    return fib(n - 1, fibs);
}


int main()
{
    const int t1 = 0;
    const int t2 = 1;
    const int  n = 6;

    std::cout << fibonacciModified(t1, t2, n) << std::endl; //Expected output: 27

    return 0;
}
