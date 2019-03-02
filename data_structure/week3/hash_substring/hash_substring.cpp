#include <iostream>
#include <list>
#include <string>
#include <vector>

using std::list;
using std::string;
using std::vector;
typedef unsigned long long ull;

const long long MULTIPLIER = 31;
const int PRIMAR = 1000000007;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

size_t hash_func(string s) {
    size_t res = 0;
    for (int i = s.size() - 1; i >= 0; --i)
        res = (res * MULTIPLIER + s[i]) % PRIMAR;

    return res;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string &s = input.pattern, t = input.text;
    vector<int> ans;
    // define the parameter for my own hash function
    // int multiplier = 263
    // prime number = 1000000007
    int ts = static_cast<int>(t.size());
    int ss = static_cast<int>(s.size());
    int _MUL_ = 1;
    for (int i = 0; i < ss; ++i)
        _MUL_ *= MULTIPLIER;

    list<size_t> hashvals;
    for (int i = ts - ss; i > -1; --i) {
        if (hashvals.size() == 0) {
            hashvals.push_back(hash_func(t.substr(i, i + ss - 1)));
        } else {
            long long lv = hashvals.front();
            long long t1 = (lv * MULTIPLIER) % PRIMAR;
            long long t2 = t[i];
            long long t3 = t[i + ss];
            long long t4 = t3 * _MUL_ % PRIMAR;
            lv = t1 + t2 - t4;
            lv = (lv + PRIMAR) % PRIMAR;

            hashvals.push_front(lv);
        }
    }
    auto ph = hash_func(s);
    int idx = 0;
    for (auto iter = hashvals.begin(); iter != hashvals.end(); ++iter) {
        if (*iter == ph) {
            ans.push_back(idx);
        }
        ++idx;
    }

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
