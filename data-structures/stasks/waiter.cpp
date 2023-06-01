/**
 * https://www.hackerrank.com/challenges/waiter/problem
 */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>


/**
 * Sieve of Eratosthenes
 * @param n: The number of primes necessaries
 * @return An array with n prime numbers in order
*/
std::vector<int> sieve(const int n)
{
    // To ensure at least n prime numbers
    const int n2 = std::max(10, n * n);

    bool* nums = new bool[n2];
    std::fill(nums, nums + n2, true);

    nums[0] = false;
    nums[1] = false;

    std::vector<int> primes;
    for (int p = 2; p < n2; ++p) {
        if (nums[p]) {
            for (int i = 2*p; i < n2; i += p) {
                nums[i] = false;
            }

            primes.push_back(p);
            if (primes.size() == n) {
                // No need to go further
                // Already found n primes
                break;
            }
        }
    }

    delete [] nums;
    return primes;
}

/**
 * @param arr: Array with numbers
 * @param q: Number of iterations
 * @return An reordered arr array following the game rules
 */
std::vector<int> waiter(const std::vector<int>& arr, const int q)
{
    // We fill A with arr values in reverse order
    std::stack<int> A;
    for (auto num : arr) {
        A.push(num);
    }

    std::vector<int> primes = sieve(q);
    std::vector<int> answers;

    std::stack<int> B;
    std::queue<int> Aaux;   // We use a queue to refill A after each iteration
    for (int i = 0; i < q; ++i) {
        while (!A.empty()) {
            const int top = A.top();
            A.pop();

            if (top % primes[i] == 0) {
                B.push(top);
            } else {
                Aaux.push(top);
            }
        }

        while (!B.empty()) {
            answers.push_back(B.top());
            B.pop();
        }

        while (!Aaux.empty()) {
            A.push(Aaux.front());
            Aaux.pop();
        }
    }

    while (!A.empty()) {
        answers.push_back(A.top());
        A.pop();
    }

    return answers;
}


int main()
{
    const int q = 1;
    const std::vector<int> arr = { 3, 4, 7, 6, 5 };

    const std::vector<int> answers = waiter(arr, q);

    // Expected output: 4 6 3 7 5
    for (auto ans : answers) {
        std::cout << ans << " ";
    }
    std::cout << std::endl;

    return 0;
}
