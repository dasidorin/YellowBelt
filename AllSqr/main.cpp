#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

using namespace std;

template <typename T1>
vector <T1> Sqr(vector <T1>& vtr) {
    for (auto& item : vtr) {
        item *= item;
    }
    return vtr;
}

template <typename First, typename Second>
pair<First, Second> operator* (pair<First, Second>& pr1, pair<First, Second> pr2) {
    return make_pair(pr1.first * pr2.first, pr1.second * pr2.second);
}

template <typename First, typename Second>
pair<First, Second>& Sqr(pair<First, Second>& pr) {
    return make_pair(pr.first * pr.first, pr.second * pr.second);
}


template <typename Key, typename Value>
map<Key, Value> Sqr(map<Key, Value>& mp) {
    for (auto& [key, value] : mp) {
        //value *= value;
        value = value * value;
    }
    return mp;
}


int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}
