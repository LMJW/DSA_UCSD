#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool islargeorequal(string a, string b) {
    int ll = a.size() + b.size();
    // compare a|b && b|a
    // if a|b > b|a
    // we conclude a>b

    for (int i = 0; i < ll; ++i) {
        char m;
        char n;
        if (i < a.size()) {
            m = a[i];
        } else {
            m = b[i - a.size()];
        }
        if (i < b.size()) {
            n = b[i];
        } else {
            n = a[i - b.size()];
        }
        if (m > n) {
            return true;
        } else if (m == n) {
            continue;
        } else {
            return false;
        }
    }
    return true;
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
