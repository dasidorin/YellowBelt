#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <sstream>

using namespace std;

template <typename Collection>
string Print(const Collection& collection, char symbol) {
    stringstream ss;
    bool first = true;

    for (const auto& item : collection) {
        if (!first) {
            ss << symbol;
        }
        first = false;
        ss << item;
    }
    return ss.str();
}

template <typename First, typename Second>
ostream& operator<< (ostream& out, const pair<First, Second> p) {
    return out << "("<< p.first << "," << p.second << ")";
}

template <typename Key, typename Value>
ostream& operator<< (ostream& out, const map<Key, Value>& m) {
    return out << "{" << Print(m, ',') << "}";
}

template <typename Value>
ostream& operator<< (ostream& out, const vector<Value>& vtr) {
    return out << "[" << Print(vtr, ',') << "]";
}

int main() {
    vector <int> vtr;

    for (int i = 1; i <= 10; ++i) {
        vtr.push_back(i);
    }
    cout << vtr << endl;

    map <int, vector<int>> mp;
    int cf = 1;
    for (int i = 1; i <= 10; ++i) {
        vector <int> current;
        for (int i = 1; i < 30; ++i) {
            current.push_back(i * cf);
        }
        if (cf < 30) {
            cf++;
        } else {
            cf = 1;
        }
        mp[i] = current;
    }
    cout << mp;
    return 0;
}
