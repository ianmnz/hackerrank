/**
 * https://www.hackerrank.com/challenges/simple-text-editor/problem
 */

#include <iostream>
#include <string>
#include <stack>


class SimpleTextEditor
{
public:
    SimpleTextEditor() {}
    ~SimpleTextEditor() { clear(); }

    /**
     * Append W to the current string
     * @param W: String to be appended
     */
    void append(const std::string& W)
    {
        // Push to the stack a pair representing an
        // append operation (true) and the appended string
        S += W;
        operations.push(std::make_pair(true, W));
    }

    /**
     * Remove last K characters of the current string
     * @param k: Number of characters to be removed
     */
    void remove(const int k)
    {
        // Push to the stack a pair representing a
        // remove operation (false) and the removed string
        const std::string removed = S.substr(S.length() - k, S.length());
        S.erase(S.length() - k);
        operations.push(std::make_pair(false, removed));
    }

    /**
     * Print the Kth character of the current string
     * @param k: Index of character + 1 to be printed
     */
    void print(const int k)
    {
        std::cout << S[k - 1] << std::endl;
    }

    /**
     * Undo last mutable operation, either append or remove
     */
    void undo()
    {
        if (!operations.empty()) {
            auto last = std::move(operations.top());
            operations.pop();

            if (last.first) {
                // If last operation is 'append',
                // we remove the appended string
                S.erase(S.length() - last.second.length());

            } else {
                // Else if the last operation is 'remove'
                // we insert again the removed string
                S += last.second;
            }
        }
    }

    /**
     * Clear stack and string
     */
    void clear()
    {
        S = "";
        while (!operations.empty()) {
            operations.pop();
        }
    }

private:
    std::string S = "";
    std::stack<std::pair<bool, std::string>> operations;
};
