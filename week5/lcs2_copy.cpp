#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

struct pos {
    int x;
    int y;
};

int threemin(int d, int y, int x) {
    int v = d;
    if (v > y) {
        v = y;
    }
    if (v > x) {
        v = x;
    }
    return v;
}

std::vector<pos> get_previous(std::vector<std::vector<int>>& dp,
                              std::vector<int>& a,
                              std::vector<int>& b,
                              int i,
                              int j) {
    std::vector<pos> res = {};
    if (i > 0 && j > 0) {
        if (a[j - 1] == b[i - 1]) {
            if (dp[i][j] == dp[i - 1][j - 1]) {
                pos p = {i - 1, j - 1};
                res.push_back(p);
            }
            if (dp[i][j] == dp[i - 1][j] + 1) {
                pos p = {i - 1, j};
                res.push_back(p);
            }
            if (dp[i][j] == dp[i][j - 1] + 1) {
                pos p = {i, j - 1};
                res.push_back(p);
            }
        } else {
            if (dp[i][j] == dp[i - 1][j - 1] + 2) {
                pos p = {i - 1, j - 1};
                res.push_back(p);
            }
            if (dp[i][j] == dp[i - 1][j] + 1) {
                pos p = {i - 1, j};
                res.push_back(p);
            }
            if (dp[i][j] == dp[i][j - 1] + 1) {
                pos p = {i, j - 1};
                res.push_back(p);
            }
        }
    } else if (i == 0 && j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
        pos p = {i, j - 1};
        res.push_back(p);
    } else if (j == 0 && i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
        pos p = {i - 1, j};
        res.push_back(p);
    }

    return res;
}

int backtrace(std::vector<std::vector<int>>& dp,
              std::vector<int>& a,
              std::vector<int>& b,
              int i,
              int j) {
    // std::cout << "calling backtrace ... \n";
    std::vector<pos> t{};
    t = get_previous(dp, a, b, i, j);
    int maxsub = 0;

    for (size_t k = 0; k < t.size(); ++k) {
        pos elem = t[k];

        int tmp = backtrace(dp, a, b, elem.x, elem.y);
        if (dp[elem.x][elem.y] == dp[i][j] && elem.x == i - 1 &&
            elem.y == j - 1) {
            ++tmp;
        }
        if (tmp > maxsub) {
            maxsub = tmp;
        }
    }
    // std::cout << maxsub << ": "
    //           << " |" << i << " " << j << " \n";
    return maxsub;
}

int lcs2(vector<int>& a, vector<int>& b) {
    int n = a.size();  // no. of cols
    int m = b.size();  // no. of rows
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));
    // int dp[n + 1][m + 1];
    // Convert 2d array to 1d for simplicity
    // int dp[(n + 1) * (m + 1)];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else {
                if (a[j - 1] == b[i - 1]) {
                    dp[i][j] = threemin(dp[i - 1][j - 1], dp[i][j - 1] + 1,
                                        dp[i - 1][j] + 1);
                } else {
                    dp[i][j] = threemin(dp[i - 1][j - 1] + 2, dp[i][j - 1] + 1,
                                        dp[i - 1][j] + 1);
                }
            }
        }
    }

    // Back trace the path, and return the maximum

    // get_previous: given a point in dp matrix, return the possible
    // points that can lead to the current position. Vaule is returned
    // by a reference vector.

    // recursive backtrace

    int count = backtrace(dp, a, b, m, n);
    return count;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}
