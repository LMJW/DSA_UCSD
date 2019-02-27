#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder {
private:
    vector<int> data_;
    vector<pair<int, int>> swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> data_[i];
    }

    void GenerateSwaps() {
        if (data_.size() == 0) {
            return;
        }
        int p = _parent(data_.size() - 1);
        while (p > -1) {
            heap_down(p, swaps_);
            p = _parent(_lchild(p) - 1);
        }
    }

    void heap_down(int p, vector<pair<int, int>>& pairs) {
        int lc = _lchild(p);
        int lr = _rchild(p);
        int t = lc;
        if (lc >= data_.size()) {
            return;
        } else if (lr >= data_.size() || data_[lc] < data_[lr]) {
        } else {
            t = lr;
        }
        if (data_[p] > data_[t]) {
            swap(data_[p], data_[t]);
            pairs.push_back(make_pair(p, t));
            heap_down(t, pairs);
        }
    }

    inline int _parent(int x) {
        if (x == 0) {
            return -1;
        } else {
            return (x - 1) / 2;
        }
    }
    inline int _lchild(int x) { return 2 * x + 1; }
    inline int _rchild(int x) { return 2 * x + 2; }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
