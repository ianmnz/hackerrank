/*
 * https://www.hackerrank.com/challenges/alice-and-bobs-silly-game/problem
 */

#include <iostream>
#include <vector>


// Sieve of Eratosthenes
int primes_up_to_n(const int n)
{
    std::vector<int> primes(n + 1, 1);
    primes[0] = 0;
    primes[1] = 0;

    int nb_primes = 0;
    for (int p = 2; p <= n; ++p) {
        if (primes[p] > 0) {
            nb_primes++;

            int k = 2;
            while(k*p <= n) {
                primes[k*p] = 0;
                k++;
            }
        }
    }

    return nb_primes;
}

bool sillyGame(const int n)
{
    const int nb_primes = primes_up_to_n(n);

    // If the number of primes up to n
    // is even, Bob is the winner
    // Otherwise Alice is the winner
    if (nb_primes % 2 == 0) {
        return false;   // Bob

    } else {
        return true;    // Alice
    }
}


int main()
{
    const int n = 5;
    std::cout << std::boolalpha << sillyGame(n) << std::endl;   // true
    return 0;
}
