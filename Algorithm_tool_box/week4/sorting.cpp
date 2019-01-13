#include <cstdlib>
#include <iostream>
#include <tuple>
#include <vector>

using std::swap;
using std::tuple;
using std::vector;

std::tuple<int, int> partition3(vector<int>& a, int l, int r) {
    int x = a[l];
    int j = l;
    int k = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] < x) {
            j++;
            k++;
            swap(a[i], a[j]);
            if (a[i] == x) {
                swap(a[i], a[k]);
            }
        } else if (a[i] == x) {
            k++;
            swap(a[i], a[k]);
        }
    }
    swap(a[l], a[j]);
    return std::make_tuple(j, k);
}

int partition2(vector<int>& a, int l, int r) {
    int x = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort(vector<int>& a, int l, int r) {
    if (l >= r) {
        return;
    }

    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    // int m = partition2(a, l, r);

    auto x = partition3(a, l, r);
    int jj = std::get<0>(x);
    int kk = std::get<1>(x);
    randomized_quick_sort(a, l, jj - 1);
    randomized_quick_sort(a, kk + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    randomized_quick_sort(a, 0, a.size() - 1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    return 0;
}
