#include <iostream>
#include <vector>

using std::vector;

vector<int> merge(vector<int> a, vector<int> b) {
    int i = 0;
    int j = 0;
    vector<int> res;
    while (i < a.size() || j < b.size()) {
        if (i < a.size() && j < b.size()) {
            if (a[i] < b[j]) {
                res.push_back(a[i]);
                ++i;
            } else {
                res.push_back(b[j]);
                ++j;
            }
        } else if (i < a.size()) {
            res.push_back(a[i]);
            ++i;
        } else {
            res.push_back(b[j]);
            ++j;
        }
    }
    return res;
}

vector<int> mergesort(vector<int> arr) {
    vector<int> left;
    vector<int> right;
    if (arr.size() > 1) {
        vector<int> l(arr.begin(), arr.begin() + arr.size() / 2);
        left = mergesort(l);
        vector<int> r(arr.begin() + arr.size() / 2, arr.end());
        right = mergesort(r);
    } else {
        return arr;
    }
    vector<int> res = merge(left, right);
    return res;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> input(n, 0);

    for (int i = 0; i < n; ++i) {
        std::cin >> input[i];
    }

    vector<int> res = mergesort(input);
    for (auto e : res) {
        std::cout << e << " ";
    }

    std::cout << "\n";
}