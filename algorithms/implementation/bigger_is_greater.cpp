/**
 * https://www.hackerrank.com/challenges/bigger-is-greater/problem
 */

#include <algorithm>
#include <iostream>
#include <string>


/**
 * @param w The string that will be increased
 * @return The next permutation of w
 */
std::string biggerIsGreater(std::string &w)
{
    /*
    // Using the std
    if (std::next_permutation(w.begin(), w.end())) {
        return w;
    } else {
        return "no answer";
    }
    */

    const int n = w.size();

    // From the right, find first non increasing element
    int pivot = -1;
    for (int i = n - 2; i >= 0; --i) {
        if (w[i] < w[i + 1]) {
            pivot = i;
            break;
        }
    }

    // If w sorted in decreasing order
    if (pivot < 0) {
        return "no answer";
    }

    // From the right, find first element bigger than
    // pivot and swap then

    /*
    // Linear search
    for (int i = n - 1; i > pivot; --i) {
        if (w[i] > w[pivot]) {
            std::swap(w[i], w[pivot]);
            break;
        }
    }
    */

    // Binary search
    const auto upper = std::upper_bound(w.rbegin(), w.rend() - pivot - 1, w[pivot]);
    std::iter_swap(upper, w.rend() - pivot - 1);

    // Reverse all elements from (pivot, end)
    std::reverse(w.begin() + pivot + 1, w.end());

    return w;
}


int main()
{
    std::string w = "dkhc";
    std::cout << biggerIsGreater(w) << std::endl;  // Expected output: hcdk
    return 0;
}
