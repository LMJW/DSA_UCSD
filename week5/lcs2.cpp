#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <vector>

using std::vector;

struct pos {
    int x;
    int y;
};

int threemin(int d, int y, int x, int& label) {
    label = 0;
    int v = d;
    if (v > y) {
        label = 1;
        v = y;
    }
    if (v > x) {
        label = 2;
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
        if (dp[i][j] - 1 == dp[i][j - 1]) {
            pos p = {i, j - 1};
            res.push_back(p);
        }
        if (dp[i][j] - 1 == dp[i - 1][j]) {
            pos p = {i - 1, j};
            res.push_back(p);
        }
        // notice about index for a, b vector
        if (dp[i][j] == dp[i - 1][j - 1] && a[j - 1] == b[i - 1]) {
            pos p = {i - 1, j - 1};
            res.push_back(p);
        } else if (dp[i][j] - 1 == dp[i - 1][j - 1]) {
            pos p = {i - 1, j - 1};
            res.push_back(p);
        };
    } else if (i == 0 && j > 0) {
        pos p = {i, j - 1};
        res.push_back(p);
    } else if (j == 0 && i > 0) {
        pos p = {i - 1, j};
        res.push_back(p);
    }
    // std::cout << "pre: "
    //           << " i: " << i << " j:" << j << " ; value = " << dp[i][j] << "
    //           |";
    // for (auto ee : res) {
    //   std::cout << ee.x << " " << ee.y << " ";
    // }
    // std::cout << " \n";
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

    for (int k = 0; k < t.size(); k++) {
        pos elem = t[k];

        int tmp = backtrace(dp, a, b, elem.x, elem.y);
        if (dp[elem.x][elem.y] == dp[i][j]) {
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
                int dir;
                dp[i][j] =
                    threemin(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j], dir);
                //! Notice the row && col index; easy to make mistake
                if (dir == 0 && a[j - 1] == b[i - 1]) {
                    ;
                } else {
                    ++dp[i][j];
                }
            }
            // std::cout << dp[i][j] << " ";
        }
        // std::cout << " \n";
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
