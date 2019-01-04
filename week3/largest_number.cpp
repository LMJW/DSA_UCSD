#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

bool islargeorequal(string a, string b) {
    int l = std::min(a.size(), b.size());
    for (int i = 0; i < l; ++i) {
        if (a[i] > b[i]) {
            return true;
        } else if (a[i] == b[i]) {
            continue;
        } else {
            return false;
        }
    }
    if (a.size() <= b.size()) {
        return true;
    }
    return false;
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
