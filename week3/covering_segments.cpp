#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using std::vector;

struct Segment {
    int start, end;
};

bool sortSeg(Segment a, Segment b) {
    return (a.start < b.start);
}

vector<int> optimal_points(vector<Segment>& segments) {
    vector<int> points;
    vector<Segment> overlap = {segments[0]};
    bool hasoverlap;
    for (size_t i = 1; i < segments.size(); ++i) {
        hasoverlap = false;
        for (int j = 0; j < overlap.size(); ++j) {
            Segment p1 = segments[i];
            Segment p2 = overlap[j];
            if (p1.start > p2.start) {
                p1 = overlap[j];
                p2 = segments[i];
            }
            // p2 will have start larger than p1
            // p2 is the overlap point
            // p1 is the incoming point

            if (p2.start <= p1.end) {
                overlap[j].start = std::max(p1.start, p2.start);
                overlap[j].end = std::min(p1.end, p2.end);
                hasoverlap = true;
            }
            if (!hasoverlap) {
                overlap.push_back(segments[i]);
            }
        }
    }

    std::sort(overlap.begin(), overlap.end(), sortSeg);
    for (auto e : overlap) {
        points.push_back(e.end);
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
