/**
 * https://www.hackerrank.com/challenges/password-cracker/problem
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


inline std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }
    ).base(), s.end());
    return s;
}

bool helper(const std::vector<std::string> &passwords,
            const std::string &loginAttempt,
            const size_t pos,
            std::stringstream &ss,
            std::vector<bool>& visited)
{
    visited[pos] = true;

    if (pos >= loginAttempt.length()) {
        return true;
    }

    const auto start = loginAttempt.begin() + pos;

    for (const auto &password : passwords) {
        const size_t length = password.length();
        const std::string match(start, start + length);

        if (match == password) {
            std::stringstream ss2;
            if (!visited[pos + length]
                && helper(passwords, loginAttempt, pos + length, ss2, visited))
            {
                ss << password << " " << ss2.str();
                return true;
            }
        }
    }

    return false;
}

std::string passwordCracker(const std::vector<std::string> &passwords, const std::string loginAttempt)
{
    std::stringstream ss;
    std::vector<bool> visited(loginAttempt.size());

    if (helper(passwords, loginAttempt, 0, ss, visited)) {
        return rtrim(ss.str());
    }

    return "WRONG PASSWORD";
}


int main()
{
    std::vector<std::string> passwords {"we", "web", "adaman", "barcod"};
    const std::string loginAttempt {"webarcodwebadamanweb"};

    std::cout << passwordCracker(passwords, loginAttempt) << std::endl; // Expected output: we barcod web adaman web

    return 0;
}
