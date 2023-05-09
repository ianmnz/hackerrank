/*
 * https://www.hackerrank.com/challenges/recursive-digit-sum/problem
 */

#include <iostream>
#include <string>


std::string find_super_digit(std::string p, const int k)
{
    if (p.size() == 1) {
        return p;
    }

    long sum = 0l;
    for (auto c : p) {
        const long digit = c - '0'; // Convert char to int

        if (0 <= digit && digit <= 9) {
            sum += digit;
        }
    }

    return find_super_digit(std::to_string(k * sum), 1);
}

int superDigit(std::string n, const int k)
{
    return std::stoi(find_super_digit(n, k));
}


int main()
{
    const int k = 4;
    const std::string n = "9875";

    std::cout << superDigit(n, k) << std::endl; // Expected output: 8

    return 0;
}
