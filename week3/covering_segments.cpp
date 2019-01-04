#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using std::vector;

// Great explain
// https://stackoverflow.com/questions/37936571/covering-segments-by-points
struct Segment {
    int start, end;
};

bool sortSeg(Segment a, Segment b) {
    return (a.end < b.end);
}

vector<int> optimal_points(vector<Segment>& segments) {
    vector<int> points;
    std::sort(segments.begin(), segments.end(), sortSeg);
    points.push_back(segments[0].end);
    int p = 0;
    for (int i = 1; i < segments.size(); ++i) {
        if (segments[i].start < points[p]) {
            continue;
        } else {
            points.push_back(segments[i].end);
            ++p;
        }
    }
    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
