/**
 * https://www.hackerrank.com/challenges/balanced-brackets/problem
 */

#include <iostream>
#include <string>
#include <stack>


/**
 * @param s: String with the brackets
 * @return true if string is balanced, false otherwise
 */
bool isBalanced(const std::string& s)
{
    std::stack<char> brackets;

    for (const char c : s) {
        // Pushing left-brackets is always allowed
        if (c == '(' || c == '{' || c == '[') {
            brackets.push(c);
            continue;
        }

        // When adding a right-bracket
        // the stack must be non-empty
        if (brackets.empty()) {
            return false;
        }

        // Check if top and right-bracket match
        // If not, return false
        if (c == ')' && (brackets.top() != '(')) {
            return false;

        } else if (c == '}' && (brackets.top() != '{')) {
            return false;

        } else if (c == ']' && (brackets.top() != '[')) {
            return false;
        }

        // If they match, pop it from the stask
        brackets.pop();
    }

    return brackets.empty();
}

int main()
{
    const std::string s = "{[(])}";
    std::cout << std::boolalpha << isBalanced(s) << std::endl;  // Expected output: false
    return 0;
}
