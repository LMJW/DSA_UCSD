#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    vector<long long> fb = {0, 1};
    vector<long long> sum = {0, 1};
    for (int i = 2;; ++i) {
        int t = fb[i - 1] + fb[i - 2];
        t %= 10;
        fb.push_back(t);
        if (t == 1 && fb[i - 1] == 0) {
            break;
        }
    }
    int l = fb.size() - 2;

    for (int i = 2;; ++i) {
        int t = sum[i - 1] + fb[i % l];
        t %= 10;
        sum.push_back(t);
        if (t == 1 && sum[i - 1] == 0) {
            break;
        }
    }
    int ll = sum.size() - 2;

    int res = sum[to % ll] + 10 - sum[from % ll] + fb[from % l];
    return res % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
}
