/**
 * https://www.hackerrank.com/challenges/aorb/problem
 */

#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>


static const std::map<char, std::string_view> h2b{
    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
};


static const std::map<std::string_view, char> b2h{
    {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
    {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
    {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
    {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'},
};


std::string hex2bin(const std::string_view H)
{
    std::stringstream ss;
    for (auto c : H) {
        ss << h2b.at(c);
    }
    return ss.str();
}

std::string bin2hex(const std::string_view B)
{
    std::stringstream ss;
    for (int i = 0; i < B.length(); i+=4) {
        ss << b2h.at(B.substr(i, 4));
    }
    auto tmp = ss.str();
    tmp.erase(0, tmp.find_first_not_of('0'));
    return tmp.empty() ? "0" : tmp;
}


/**
 * @param K Max number of changes
 * @param xA String of A in hex
 * @param xB String of B in hex
 * @param xC String of C in hex
 * @return Optional pair of modified A' and B' such as A'|B' == C
 */
std::optional<std::pair<std::string, std::string>> aOrB(
    int K,
    const std::string &xA,
    const std::string &xB,
    const std::string &xC)
{
    std::string bA = hex2bin(xA);
    std::string bB = hex2bin(xB);
    std::string bC = hex2bin(xC);

    const long n = std::max(bC.length(), std::max(bA.length(), bB.length()));

    // Prepend strings with '0'
    bA.insert(0, n - bA.length(), '0');
    bB.insert(0, n - bB.length(), '0');
    bC.insert(0, n - bC.length(), '0');

    for (long i = 0; i < n; ++i) {
        if (bC[i] == '0') {
            // If Ci is 0, then both Ai and Bi must be 0
            // If either is 1, then change it to 0 and decrement the
            // number of available changes
            if (bA[i] == '1') { bA[i] = '0'; --K; }
            if (bB[i] == '1') { bB[i] = '0'; --K; }

        } else if (bC[i] == '1') {
            // If Ci is 1, then either Ai or Bi (or both) is 1
            // If both are 0, then choose one of then to be 1
            // Since we try to minimize A, we choose B
            if (bA[i] == '0' && bB[i] == '0') { bB[i] = '1'; --K; }
        }
    }

    if (K < 0) {
        // Not possible to modify A and B in less than K changes
        // and get A' | B' == C
        return std::nullopt;

    } else {
        // Try to find the solution that minimizes A' and B' that
        // respect the condition above
        for (long i = 0; i < n; ++i) {
            if (bA[i] == '0') {
                // If Ai is zero, then it is already
                // in its minimal valid state
                continue;
            }

            if (bB[i] == '1' && (K >= 1)) {
                // Else, if Bi is also 1 and we have at least one
                // change available, we can decrement A by setting
                // Ai to 0
                bA[i] = '0';
                --K;

            } else if (bB[i] == '0' && (K >= 2)) {
                // Else, if Bi is 0 and we have at least two
                // changes available, we can swap then out
                // setting Ai to 0 and Bi to 1
                bA[i] = '0';
                bB[i] = '1';
                K -= 2;
            }
        }

        return std::make_pair(bin2hex(bA), bin2hex(bB));
    }
}


int main()
{
    const int K = 54;
    const std::string A = "8CC5695B3A257A0BB671";
    const std::string B = "833A22A3496652BBC06F";
    const std::string C = "D85125CEB4F372EA58D9";

    const auto res = aOrB(K, A, B, C);
    if (res.has_value()) {
        // Expected output: 14A3021720A1051 D851248684F252EA48C9
        std::cout << res.value().first << "\n" << res.value().second << std::endl;
    }

    return 0;
}
