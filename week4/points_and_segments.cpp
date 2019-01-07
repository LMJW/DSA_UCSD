#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

bool sortint(int a, int b) {
    return a < b;
}

int bsearch(vector<int> a, int b) {
    int i = 0;
    int j = a.size();
    while (i < j) {
        int t = (i + j) / 2;
        if (b > a[t]) {
            i = t + 1;
        } else if (b < a[t]) {
            j = t;
        } else {
            return t;
        }
    }
    return std::min(i, j);
}

vector<int> fast_count_segments(vector<int> starts,
                                vector<int> ends,
                                vector<int> points) {
    vector<int> cnt(points.size());
    // write your code here
    std::sort(starts.begin(), starts.end(), sortint);
    std::sort(ends.begin(), ends.end(), sortint);
    for (int i = 0; i < points.size(); ++i) {
        int e = points[i];
        int left = bsearch(starts, e);
        int right = bsearch(ends, e);
        int t = 0;
        if (e >= starts[left]) {
            t += (left + 1);
        } else {
            t += left;
        }
        if (e > ends[right]) {
            t -= (right + 1);
        } else {
            t -= right;
        }
        cnt[i] = t;
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
    vector<int> cnt = naive_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt.size(); i++) {
        std::cout << cnt[i] << ' ';
    }
}
