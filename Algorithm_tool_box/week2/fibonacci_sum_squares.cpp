#include <iostream>
#include <vector>

using std::vector;

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;
    vector<int> fb = {0, 1};
    for (int i = 2;; i++) {
        int t = fb[i - 1] + fb[i - 2];
        t %= 10;
        fb.push_back(t);
        if (t == 1 && fb[i - 1] == 0) {
            break;
        }
    }
    int l = fb.size() - 2;

    return fb[(n + 1) % l] * fb[n % l] % 10;
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_squares_naive(n);
}
