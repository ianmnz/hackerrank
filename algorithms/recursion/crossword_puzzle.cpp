/**
 * https://www.hackerrank.com/challenges/crossword-puzzle/problem
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


/**
 * @param str: String of words separated by delimiter
 * @param delimiter: Delimiter separating words (size = 1)
 * @return Array with separeted words of string
 */
std::vector<std::string> split(const std::string& str, const std::string& delimiter)
{
    size_t pos_start = 0, pos_end;
    std::vector<std::string> tokens;
    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        tokens.push_back(str.substr(pos_start, pos_end - pos_start));
        pos_start = pos_end + 1;
    }

    tokens.push_back(str.substr(pos_start));
    return tokens;
}

/**
 * @param x: Row index
 * @param y: Column index
 * @param crossword: Crossword matrix
 * @param word: Word to check if it fits horizontally
 * @return True if it fits, false otherwise
 */
bool checkHorizontal(const int x, const int y,
                     std::vector<std::string>& crossword,
                     const std::string& word)
{
    if (y >= 1 && crossword[x][y - 1] != '+') {
        return false;
    }

    const int n = word.length();

    for (int i = 0; i < n; i++) {
        if (crossword[x][y + i] == '-' || crossword[x][y + i] == word[i]) {
            crossword[x][y + i] = word[i];

        } else {
            return false;
        }
    }

    if ((y + n) < crossword.size() && crossword[x][y + n] != '+') {
        return false;
    }
    return true;
}

/**
 * @param x: Row index
 * @param y: Column index
 * @param crossword: Crossword matrix
 * @param word: Word to check if it fits vertically
 * @return True if it fits, false otherwise
 */
bool checkVertical(const int x, const int y,
                   std::vector<std::string>& crossword,
                   const std::string& word)
{
    if (x >= 1 && crossword[x - 1][y] != '+') {
        return false;
    }

    const int n = word.length();

    for (int i = 0; i < n; i++) {
        if (crossword[x + i][y] == '-' || crossword[x + i][y] == word[i]) {
            crossword[x + i][y] = word[i];

        } else {
            return false;
        }
    }

    if ((x + n) < crossword.size() && crossword[x + n][y] != '+') {
        return false;
    }
    return true;
}

/**
 * @param crossword: Crossword matrix
 * @return True if crossword solved, false otherwise
 */
bool solved(const std::vector<std::string>& crossword)
{
    for (int i = 0; i < crossword.size(); ++i) {
        for (int j = 0; j < crossword.size(); ++j) {
            if (crossword[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

/**
 * @param crossword: Crossword matrix
 * @param words: Array of words to solve crossword
 * @param word_idx: Current word index on the words array
 * @return True if crossword solved, false otherwise
 */
bool solve(std::vector<std::string>& crossword, const std::vector<std::string>& words, int word_idx)
{
    if (word_idx >= words.size()) {
        return true;
    }

    const int n = crossword.size();
    const std::string word = words[word_idx];
    const int blankLength = n - word.length();

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x <= blankLength; ++x) {
            const std::vector<std::string> backup = crossword;
            if (checkVertical(x, y, crossword, word)) {
                if (!solve(crossword, words, ++word_idx)) {
                    --word_idx;
                    crossword = backup;
                }
            } else {
                crossword = backup;
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y <= blankLength; ++y) {
            const std::vector<std::string> backup = crossword;
            if (checkHorizontal(x, y, crossword, word)) {
                if (!solve(crossword, words, ++word_idx)) {
                    --word_idx;
                    crossword = backup;
                }
            } else {
                crossword = backup;
            }
        }
    }
    return solved(crossword);
}

/**
 * @param crossword: Crossword matrix
 * @param words: String of words to solve crossword separated by ';'
 */
void crosswordPuzzle(std::vector<std::string>& crossword, const std::string& words)
{
    std::vector<std::string> tokens = split(words, ";");

    std::sort(tokens.begin(), tokens.end(),
    [](const std::string& lhs, const std::string& rhs)
    {
        return lhs.length() > rhs.length();
    });

    for (auto& word : tokens) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    solve(crossword, tokens, 0);
}


int main()
{
    std::vector<std::string> crossword = {
        "++++++-+++",
        "++------++",
        "++++++-+++",
        "++++++-+++",
        "+++------+",
        "++++++-+-+",
        "++++++-+-+",
        "++++++++-+",
        "++++++++-+",
        "++++++++-+"
    };

    const std::string words = "ICELAND;MEXICO;PANAMA;ALMATY";

    crosswordPuzzle(crossword, words);

    /* Expected output:
     * ++++++I+++
     * ++MEXICO++
     * ++++++E+++
     * ++++++L+++
     * +++PANAMA+
     * ++++++N+L+
     * ++++++D+M+
     * ++++++++A+
     * ++++++++T+
     * ++++++++Y+
     */
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << crossword[i][j];
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    return 0;
}
