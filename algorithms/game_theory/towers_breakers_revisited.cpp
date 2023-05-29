/**
 * https://www.hackerrank.com/challenges/tower-breakers-revisited-1/problem
 */

#include <iostream>
#include <vector>
#include <map>


// For performance issues, we cache the number
// of prime factors in a global map
std::map<int, int> nbPrimeFactors;

/**
 * @param K: A positive integer
 * @return The number of prime factors of K
 */
int countPrimeFactors(const int K)
{
    if (K == 1) {
        return 0;

    } else if (const int prev = nbPrimeFactors[K]; prev != 0) {
        // It was previously calculated
        return prev;
    }

    // Iteratively check the number of prime factors of K
    int nb_factors = 0;
    for (int p = 2, k = K; p <= k; ++p) {
        while (k % p == 0) {
            nb_factors++;
            k /= p;
        }
    }

    // We cache it to avoid reiterating
    nbPrimeFactors[K] = nb_factors;
    return nb_factors;
}

/**
 * @param arr: Array with the towers' heights
 * @return The winner, either 1 for Player 1 or 2 for Player 2
 */
int towerBreakers(const std::vector<int>& arr)
{
    int nimSum = 0;
    for (auto K : arr) {
        // It is a modified Nim game where only
        // the prime factor's count of each
        // tower's height counts
        nimSum ^= countPrimeFactors(K);
    }
    return nimSum? 1 : 2;
}


int main()
{
    const std::vector<int> arr = {1, 2, 3};
    std::cout << towerBreakers(arr) << std::endl;   // Expected output: 2
    return 0;
}
