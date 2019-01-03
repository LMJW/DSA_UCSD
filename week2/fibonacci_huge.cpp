#include <iostream>
#include <vector>

using std::vector;

long long get_fibonacci_huge_naive(long long n, long long m) {
    vector<long long> table;
    table.push_back(0);
    table.push_back(1);
    for (long long i = 2;; ++i) {
        long long t = table[i - 1] + table[i - 2];
        t %= m;
        table.push_back(t);
        if (t == 1 && table[i - 1] == 0) {
            break;
        }
    }
    int l = table.size() - 1;
    int r = n % l;

    for (auto e : table) {
        std::cout << e << " ";
    }
    std::cout << " \n";

    return table[r];
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
