/**
 * https://www.hackerrank.com/challenges/encryption/problem
 */

#include <iostream>
#include <cmath>
#include <string>


/**
 * @param s: String to be encrypted
 * @return Encrypted string
 */
std::string encryption(std::string& s)
{
    const int L = s.length();
    int rows = std::floor(std::sqrt(L));
    int cols = std::ceil(std::sqrt(L));

    if ((rows * cols < L)) {
        rows += 1;
    }

    // We pad the end of the string with enough
    // spaces to complete the rows * cols grid
    const int pad = rows * cols - L;
    s.append(pad, ' ');

    std::string res = "";
    for (int j = 0; j < cols; ++j) {
        std::string buffer = "";

        // We retrieve each column to form
        // the next buffer
        for (int i = 0; i < rows; ++i) {
            const char c = s[cols * i + j];

            if (c != ' ') {
                buffer += c;
            }
        }

        res += buffer + ' ';
    }

    return res;
}


int main()
{
    std::string s = "feedthedog";
    std::cout << encryption(s) << std::endl;    // Expected output: fto ehg ee dd
    return 0;
}
