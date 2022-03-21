#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

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
        /*int current_counter = count(regions.begin(), regions.end(), item);
        if (current_counter > current_max) {
            current_max = current_counter;
        }*/
        current_max = max(current_max, ++region_count[item]);
    }

    return current_max;
}

/*int main() {

    Region region0 {"Moscow",
                    "Russia",
                    {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                    89};

    Region region1;
    Region region2 {"Moscow",
                    "Russia",
                    {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                    90};
    Region region3 {"Moscow",
                    "Russia",
                    {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                    89};
    Region region4 {"Moscow",
                    "Russia",
                    {{Lang::DE, "Moska"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                    89};

    Region region5 {"Lissabon",
                    "Russia",
                    {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                    89};

    Region region6 {"Moscow",
                    "Germany",
                    {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                    89};

    vector <Region> regions {region0,
                             region1,
                             region2,
                             region3,
                             region4,
                             region5,
                             region6};

    cout << "Operator == " << endl << endl;
    for (size_t i = 1; i < regions.size(); ++i) {
        cout << "Test " + to_string(i) + ": ";
        if (regions[i] == regions[0] && i != 3) {
            cout << "[FAILED]";
        } else {
            cout << "[OK]";
        }
        cout << endl;
    }

    cout << FindMaxRepetitionCount(regions) << endl;
    return 0;
}
*/

int main() {
    cout << FindMaxRepetitionCount({
                                           {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Russia",
                                                   "Eurasia",
                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Russia",
                                                   "Eurasia",
                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                                                   89
                                           },
                                   }) << endl;

    cout << FindMaxRepetitionCount({
                                           {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Russia",
                                                   "Eurasia",
                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Toulouse",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   31
                                           },
                                   }) << endl;

    return 0;
}
