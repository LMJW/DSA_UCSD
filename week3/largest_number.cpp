#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool islargeorequal(string a, string b) {
    int ll = std::max(a.size(), b.size());
    for (int i = 0; i < ll; ++i) {
        char m;
        char n;
        if (i < a.size() && i < b.size()) {
            char m = a[i];
            char n = b[i];
        } else if (i >= a.size()) {  // a string is the shorter string
            int idx = i - a.size();
            char m = b[idx];
            char n = b[i];
        } else if (i >= b.size()) {  // b string is the shorter string
            int idx = i - b.size();
            char m = a[i];
            char n = a[idx];
        }
        if (m > n) {
            return true;
        } else if (m == n) {
            continue;
        } else {
            return false;
        }
    }
    // this is still buggy
    // given 323 32 && 191 19
    // they behave differently
    return true;
}
}

string largest_number(vector<string> a) {
    std::stringstream ret;

    string ele = a.back();
    a.pop_back();
    while (a.size() > 0) {
        for (int i = 0; i < a.size(); ++i) {
            if (!islargeorequal(ele, a[i])) {
                string t = ele;
                ele = a[i];
                a[i] = t;
            }
        }
        ret << ele;
        ele = a.back();
        a.pop_back();
    }
    ret << ele;

    string result;
    ret >> result;
    if (result[0] == '0') {
        return "0";
    }
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);
}
