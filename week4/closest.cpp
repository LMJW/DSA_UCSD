#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::min;
using std::pair;
using std::string;
using std::vector;

vector<pair<int, int>> mergesort(vector<pair<int, int>> ps) {
    if (ps.size() < 2) {
        return ps;
    }
    vector<pair<int, int>> res;
    vector<pair<int, int>> left(ps.begin(), ps.begin() + ps.size() / 2);
    vector<pair<int, int>> right(ps.begin() + ps.size() / 2, ps.end());
    left = mergesort(left);
    right = mergesort(right);
    size_t i, j, c;
    i = 0;
    j = 0;
    for (c = 0; c < ps.size(); ++c) {
        if (i < left.size() && j < right.size()) {
            if (left[i].first < right[j].first) {
                res.push_back(left[i]);
                ++i;
            } else {
                res.push_back(right[j]);
                ++j;
            }
        } else if (i < left.size()) {
            res.push_back(left[i]);
            ++i;
        } else {
            res.push_back(right[j]);
            ++j;
        }
    }
    return res;
}

double minimal_distance(vector<int> x, vector<int> y) {
    vector<pair<int, int>> points;
    for (size_t i = 0; i < x.size(); ++i) {
        points.push_back(std::make_pair(x[i], y[i]));
    }
    points = mergesort(points);
    for (auto e : points) {
        std::cout << e.first << " " << e.second << " \n";
    }
    return 0.;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::fixed;
    std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
