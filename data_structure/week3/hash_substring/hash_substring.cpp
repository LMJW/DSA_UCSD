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

// only calculate at the first time
size_t hash_func(const string& s, int start, int pattern) {
    size_t res = 0;
    for (int i = start + pattern - 1; i >= start; --i)
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

    long long _POWER_MOD = 1;
    for (int i = 0; i < s.size(); ++i)
        _POWER_MOD = (_POWER_MOD * MULTIPLIER) % PRIMAR;

    list<size_t> hashvals;
    for (int i = t.size() - s.size(); i > -1; --i) {
        if (hashvals.size() == 0) {
            hashvals.push_back(hash_func(t, i, s.size()));
        } else {
            long long lv = hashvals.front();
            long long t1 = (lv * MULTIPLIER) % PRIMAR;
            long long t2 = t[i];
            // long long t3 = t[i + s.size()];
            /// This part can be computational intensive as we need to go
            /// through this process for all substrings
            /// (a*x^m)%p= a%p * x^m%p
            /// so we can calculate x^m first and then do the multiplication

            /// the following commented code's time complexity is a bit too high
            /**
             * for (int j = 0; j < s.size(); ++j)
             *   t3 = (t3 * MULTIPLIER) % PRIMAR;
             */
            long long t3 = t[i + s.size()] * _POWER_MOD % PRIMAR;

            lv = (t1 + t2 - t3 + PRIMAR) % PRIMAR;

            hashvals.push_front(lv);
        }
    }
    auto ph = hash_func(s, 0, s.size());
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
