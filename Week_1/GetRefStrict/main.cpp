#include <iostream>
#include <map>
#include <exception>
#include <string>

using namespace std;

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& mp, const Key& k) {
    if (!mp.count(k)) {
        throw runtime_error("");
    }
    return mp[k];
}

int main() {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;
    return 0;
}
