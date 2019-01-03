#include <iostream>
#include <vector>

using std::vector;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    vector<long long> table = {0, 1};
    vector<long long> sum = {0, 1};

    for (int i = 2;; ++i) {
        int t = table[i - 1] + table[i - 2];
        t %= 10;
        table.push_back(t);
        if (t == 1 && table[i - 1] == 0) {
            break;
        }
    }
    int l = table.size() - 2;

    for (int i = 2;; ++i) {
        int t = sum[i - 1] + table[i % l];
        t %= 10;
        sum.push_back(t);
        if (t == 1 && sum[i - 1] == 0) {
            break;
        }
    }
    int ll = sum.size() - 2;

    // for (auto e : table) {
    //     std::cout << e << " ";
    // }
    // std::cout << "\n";

    // for (auto e : sum) {
    //     std::cout << e << " ";
    // }
    // std::cout << "\n";

    return sum[n % ll];
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_naive(n);
}
