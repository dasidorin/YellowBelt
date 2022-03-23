#include <iostream>
#include <vector>

using namespace std;

class Block {
public:
    Block (){
        width = 0;
        high = 0;
        length = 0;
    }

    Block (long int new_width, long int new_high, long int new_length) {
        width = new_width;
        high = new_high;
        length = new_length;
    }

    unsigned long long int GetVolume() const{
        return (width * high * length);
    }

private:
    unsigned long int width;
    unsigned long int high;
    unsigned long int length;
};

int main() {
    unsigned int block_count = 0;
    unsigned int ro = 0;

    cin >> block_count >> ro;
    vector <Block> blocks (block_count);
    for (int i = 0; i < block_count; ++i) {
        long int current_width = 0;
        long int current_high = 0;
        long int current_length = 0;

        cin >> current_width >> current_high >> current_length;
        blocks.push_back(Block(current_width,current_high, current_length));
    }

    unsigned long long int sum_wight = 0;
    for (const auto& block : blocks) {
        sum_wight += (ro * block.GetVolume());
    }
    cout << sum_wight << endl;
    return 0;
}
