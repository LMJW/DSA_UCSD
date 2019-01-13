#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int>& w) {
    int n = w.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < W + 1; ++j) {
            if (i == 0 || j == 0) {
                ;
            } else if (j < w[i - 1]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                int r = j - w[i - 1];
                int t1 = dp[i - 1][r] + w[i - 1];
                int t2 = dp[i - 1][j];
                dp[i][j] = std::max(t1, t2);
            }
        }
    }
    // for (auto& row : dp) {
    //     std::cout << "\n";
    //     for (auto col : row) {
    //         std::cout << col << " ";
    //     }
    // }
    return dp[n][W];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
