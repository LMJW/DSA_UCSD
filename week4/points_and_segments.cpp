#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

vector<vector<int>> mergesort(vector<vector<int>> arr) {
    if (arr.size() < 2) {
        return arr;
    }
    size_t t = arr.size();
    vector<vector<int>> res(0, vector<int>(2));
    vector<vector<int>> left(arr.begin(), arr.begin() + t / 2);
    vector<vector<int>> right(arr.begin() + t / 2, arr.end());
    left = mergesort(left);
    right = mergesort(right);
    size_t i = 0;
    size_t j = 0;

    for (size_t c = 0; c < t; ++c) {
        if (i < left.size() && j < right.size()) {
            if (left[i][0] < right[j][0]) {
                res.push_back(left[i]);
                ++i;
            } else if (left[i][0] > right[j][0]) {
                res.push_back(right[j]);
                ++j;
            } else {
                // if value equal, sort base on the second value
                // base on analysis. left edge point should sort
                // before target points, and then the right points
                //
                if (left[i][1] > right[j][1]) {
                    res.push_back(left[i]);
                    ++i;
                } else if (left[i][1] < right[j][1]) {
                    res.push_back(right[j]);
                    ++j;
                } else {
                    std::cout << "should not happen\n";
                }
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

vector<int> fast_count_segments(vector<int> starts,
                                vector<int> ends,
                                vector<int> points) {
    vector<int> cnt(points.size());

    // int total = starts.size() + ends.size() + points.size();
    vector<vector<int>> allpoints;
    unordered_map<int, int> pmap;
    for (size_t i = 0; i < points.size(); ++i) {
        pmap.insert({i, 0});
    }
    // use length 2 vector to represent a point
    // the first element is the point value
    // the second element is the point type
    // if it's the left point of a range, it equals to 1
    // if it's the right end of a range, it equals to -1
    // if it's a target point, it equals to 0
    //
    // The advantage of using 1, 0, -1 is that this is
    // easy to calculate the end value.
    //
    // we can used the merge sort to solve all the points
    // and finally use linear time to calculate all the
    // points values.
    for (size_t i = 0; i < starts.size(); ++i) {
        allpoints.push_back(vector<int>{starts[i], 1});
    }

    for (size_t i = 0; i < ends.size(); ++i) {
        allpoints.push_back(vector<int>{ends[i], -1});
    }

    for (size_t i = 0; i < points.size(); ++i) {
        allpoints.push_back(vector<int>{points[i], 0});
    }
    auto res = mergesort(allpoints);

    int sum = 0;

    for (size_t i = 0; i < res.size(); ++i) {
        // std::cout << res[i].size() << " |";
        // for (auto e : res[i]) {
        //     std::cout << e << " ";
        // }
        // std::cout << "\n";
        sum += res[i].at(1);
        auto search = pmap.find(res[i][0]);
        if (res[i][1] == 0 && search != pmap.end()) {
            // pmap[res[i][0]] = sum;
            pmap.insert({res[i][0], sum});
        }
        // std::cout << "??";
    }

    // for (auto& ele : res) {

    //     sum += ele[1];
    //     auto search = pmap.find(ele[0]);
    //     if (ele[1] == 0 && search != pmap.end()) {
    //         pmap[ele[0]] = sum;
    //     }
    // }
    for (size_t i = 0; i < points.size(); ++i) {
        auto s = pmap.find(points[i]);
        std::cout << points[i] << ";\n";
        if (s != pmap.end()) {
            cnt[i] = s->second;
        } else {
            std::cout << "?\n";
        }
    }

    return cnt;
}

vector<int> naive_count_segments(vector<int> starts,
                                 vector<int> ends,
                                 vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    // use fast_count_segments
    vector<int> cnt = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
