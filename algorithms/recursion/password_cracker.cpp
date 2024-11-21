/**
 * https://www.hackerrank.com/challenges/password-cracker/problem
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


/**
 * @param s string to be right-trimmed
 * @return the right-trimmed string
 */
inline std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }
    ).base(), s.end());
    return s;
}

/**
 * @brief Recursive DFS helper function
 *
 * @param passwords Array of all passwords
 * @param loginAttempt String concatenating (or not) the passwords
 * @param pos Current position in loginAttempt
 * @param ss String output
 * @param visited Array of bool to check if position was already visited
 * @return true if loginAttempt concatenates passwords,
 * @return false otherwise
 */
bool dfs(const std::vector<std::string> &passwords,
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
                && dfs(passwords, loginAttempt, pos + length, ss2, visited))
            {
                ss << password << " " << ss2.str();
                return true;
            }
        }
    }

    return false;
}

/**
 * @param passwords Array of all passwords
 * @param loginAttempt String concatenating (or not) the passwords
 * @return Passwords used to concatenate loginAttempt or 'WRONG PASSWORD'
 */
std::string passwordCracker(const std::vector<std::string> &passwords, const std::string loginAttempt)
{
    std::stringstream ss;
    std::vector<bool> visited(loginAttempt.size());

    if (dfs(passwords, loginAttempt, 0, ss, visited)) {
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
