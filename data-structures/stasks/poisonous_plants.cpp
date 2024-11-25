/**
 * https://www.hackerrank.com/challenges/poisonous-plants/problem
 */

#include <iostream>
#include <stack>
#include <vector>


struct Plant
{
    int pesticide_lvl;
    int day_of_death;  // 0 if it survived
};

/**
 * @param pesticide_levels Array with pesticide levels
 * @return The nb days it took to last non-surviving plant to die
 */
int poisonousPlants(std::vector<int> &pesticide_levels)
{
    int nb_days = 0;
    std::stack<Plant> stk;

    for (int i = 0; i < pesticide_levels.size(); ++i) {
        const int pesticide_lvl = pesticide_levels[i];
        int dod = 0;  // day of death

        // At this stage, the stack, if not empty,
        // is in ascending order in terms of pesticide levels:
        // The base has the inferior pesticide level
        // being the rightmost surviving plant up to (i-1).
        // All above elements will die on (day_of_death)-th iteration
        while (!stk.empty() && stk.top().pesticide_lvl >= pesticide_lvl) {
            dod = std::max(dod, stk.top().day_of_death);
            stk.pop();
        }

        if (stk.empty()) {
            // Either the first plant or
            // the rightmost surviving plant up to (i)
            // i. e., all plants to the right will at most
            // look up to here to check if it survives as well
            // so we can ignore the lefthand side
            dod = 0;

        } else {
            // The i-th plant will die on (day_of_death)-th iteration
            // The (nb_days) variable keeps track of how long it took
            // to the last non-surviving plant to die
            nb_days = std::max(nb_days, ++dod);
        }

        stk.push({pesticide_lvl, dod});
    }

    return nb_days;
}


int main(int argc, char const *argv[])
{
    std::vector<int> pesticides{6, 5, 8, 4, 7, 10, 9};
    std::cout << poisonousPlants(pesticides) << std::endl;  // Expected output: 2

    return 0;
}
