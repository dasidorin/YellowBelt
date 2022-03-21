#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

bool operator< (const Region& lhs, const Region& rhs) {
    return  tie(lhs.std_name,
                lhs.parent_std_name,
                lhs.names,
                lhs.population) <
            tie(rhs.std_name,
                rhs.parent_std_name,
                rhs.names,
                rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {

    int current_max = 0;
    map <Region, int> region_count;

    for (const auto& item : regions) {
        current_max = max(current_max, ++region_count[item]);
    }

    return current_max;
}

