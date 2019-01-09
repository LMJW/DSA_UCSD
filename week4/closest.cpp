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

vector<pair<int, int>> mergesort(vector<pair<int, int>> ps, int idx) {
    // idx = 0 means on sort by x
    // idx = 1 means on sort by y
    if (ps.size() < 2) {
        return ps;
    }
    vector<pair<int, int>> res;
    vector<pair<int, int>> left(ps.begin(), ps.begin() + ps.size() / 2);
    vector<pair<int, int>> right(ps.begin() + ps.size() / 2, ps.end());
    left = mergesort(left, idx);
    right = mergesort(right, idx);
    size_t i, j, c;
    i = 0;
    j = 0;
    for (c = 0; c < ps.size(); ++c) {
        if (i < left.size() && j < right.size()) {
            switch (idx) {
                case 0:
                    if (left[i].first < right[j].first) {
                        res.push_back(left[i]);
                        ++i;
                    } else {
                        res.push_back(right[j]);
                        ++j;
                    }
                    break;
                case 1:
                    if (left[i].second < right[j].second) {
                        res.push_back(left[i]);
                        ++i;
                    } else {
                        res.push_back(right[j]);
                        ++j;
                    }
                    break;
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

double distance(pair<int, int>& p1, pair<int, int>& p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return sqrt(dx * dx + dy * dy);
}

double min_dis(vector<pair<int, int>> ps) {
    if (ps.size() < 2) {
        return std::numeric_limits<double>::infinity();
    } else if (ps.size() == 2) {
        return distance(ps[0], ps[1]);
    }
    vector<pair<int, int>> left(ps.begin(), ps.begin() + ps.size() / 2);
    vector<pair<int, int>> right(ps.begin() + ps.size() / 2, ps.end());

    auto dl = min_dis(left);
    auto dr = min_dis(right);

    auto d = std::min(dl, dr);

    double splitx = (left[left.size() - 1].first + right[0].first) / 2;

    vector<pair<int, int>> satisfypoints;
    for (auto& ele : ps) {
        auto t = fabs(splitx - ele.first);
        if (t <= d) {
            satisfypoints.push_back(ele);
        }
    }

    satisfypoints = mergesort(satisfypoints, 1);

    for (size_t i = 0; i + 1 < satisfypoints.size(); ++i) {
        for (size_t j = 1; j < 8; ++j) {
            if (i + j < satisfypoints.size()) {
                auto v = distance(satisfypoints[i], satisfypoints[i + j]);
                if (v < d) {
                    d = v;
                }
            }
        }
    }

    return d;
}

double minimal_distance(vector<int> x, vector<int> y) {
    vector<pair<int, int>> points;
    for (size_t i = 0; i < x.size(); ++i) {
        points.push_back(std::make_pair(x[i], y[i]));
    }
    points = mergesort(points, 0);
    // for (auto e : points) {
    //     std::cout << e.first << " " << e.second << " \n";
    // }

    return min_dis(points);
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
