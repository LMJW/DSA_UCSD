#include <iostream>
#include <vector>

using std::vector;

int threemax(int a, int b, int c) {
    int v = a;
    if (v < b) {
        v = b;
    }
    if (v < c) {
        v = c;
    }
    return v;
}

int lcs3(vector<int>& a, vector<int>& b, vector<int>& c) {
    int n = a.size();
    int m = b.size();
    int g = c.size();
    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(m + 1, vector<int>(g + 1, 0)));

    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            for (int k = 0; k < g + 1; ++k) {
                if (i == 0 || j == 0 || k == 0) {
                    dp[i][j][k] = 0;
                } else if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;
                } else {
                    dp[i][j][k] = threemax(dp[i - 1][j][k], dp[i][j - 1][k],
                                           dp[i][j][k - 1]);
                }
            }
        }
    }
    return dp[n][m][g];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
