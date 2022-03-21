#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    vector <long int> temp;

    for (int i = 0; i < n; ++i) {
        long int current_temp = 0;
        cin >> current_temp;
        temp.push_back(current_temp);
    }

    long int avg = 0;
    for (size_t i = 0; i < temp.size(); ++i) {;
        avg += temp[i];
    }

    avg /= static_cast<long int>(temp.size());

    int counter_more = 0;
    for (size_t i = 0; i < temp.size(); ++i) {
        if (temp[i] > avg) {
            counter_more++;
        }
    }

    cout << counter_more << endl;
    for (size_t i = 0; i < temp.size(); ++i) {
        if (temp[i] > avg) {
            cout << i << " ";
        }
    }
    return 0;
}
