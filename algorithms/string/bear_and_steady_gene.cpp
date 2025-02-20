/**
 * https://www.hackerrank.com/challenges/bear-and-steady-gene/problem
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <string_view>


/**
 * @param freq Map of frequencies
 * @param target The common target of all frequencies
 * @return true if all respect the target
 * @return false otherwise
 */
bool is_stable(const std::map<char, int> &freq, const int target)
{
    return std::all_of(freq.cbegin(), freq.cend(),
                       [target](auto kv) { return kv.second <= target; });
}


/**
 * @param gene String_view of the gene sequence
 * @return int The smallest substring size to make the gene stable
 */
int steadyGene(const std::string_view gene)
{
    std::map<char, int> freq{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}};

    // Count base frequency in gene
    for (const char base : gene) {
        freq[base]++;
    }

    const int n = gene.length();

    auto is_gene_stable = [n, &freq]() { return is_stable(freq, n / 4); };

    // If it is already stable, nothing to do
    if (is_gene_stable()) {
        return 0;
    }

    int substr_len = n;
    int left = 0, right = 0;

    for (; left < n; ++left) {
        // Find first stable configuration
        while (right < n && !is_gene_stable()) {
            --freq[gene[right]];
            ++right;
        }

        // Minimizes size of substring
        if (is_gene_stable()) {
            substr_len = std::min(substr_len, right - left);
        }

        ++freq[gene[left]];
    }

    return substr_len;
}


int main(int argc, char const *argv[])
{
    const std::string_view sv = "TGATGCCGTCCCCTCAACTTGAGTGCTCCTAATGCGTTGC";
    std::cout << steadyGene(sv) << std::endl;   // Expected output: 5
    return 0;
}
