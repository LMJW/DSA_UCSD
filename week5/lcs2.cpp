#include <functional>
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

int lcs2(vector<int>& a, vector<int>& b) {
  int n = a.size();
  int m = b.size();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
  // int dp[n + 1][m + 1];
  // Convert 2d array to 1d for simplicity
  // int dp[(n + 1) * (m + 1)];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (i == 0) {
        dp[i][j] = j;
      } else if (j == 0) {
        dp[i][j] = i;
      } else {
        int dir;
        dp[i][j] = threemin(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j], dir);
        if (dir == 0 && a[i - 1] == b[j - 1]) {
          ;
        } else {
          ++dp[i][j];
        }
      }
    }
  }

  // Back trace the path, and return the maximum

  // get_previous: given a point in dp matrix, return the possible
  // points that can lead to the current position. Vaule is returned
  // by a reference vector.
  auto get_previous = [&](int i, int j) {
    std::vector<pos> res;
    if (i > 0 && j > 0) {
      if (dp[i][j] - 1 == dp[i][j - 1]) {
        pos p = {i, j - 1};
        res.push_back(p);
      }
      if (dp[i][j] - 1 == dp[i - 1][j]) {
        pos p = {i - 1, j};
        res.push_back(p);
      }
      if (dp[i][j] == dp[i - 1][j - 1] && a[i - 1] == b[j - 1]) {
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
    return res;
  };

  std::function<int(int, int)> backtrace;
  // recursive backtrace
  backtrace = [&](int i, int j) -> int {
    std::vector<pos> t = get_previous(i, j);
    int maxsub = 0;
    while (t.size() > 0) {
      for (auto& elem : t) {
        int tmp = backtrace(elem.x, elem.y);
        if (dp[elem.x][elem.y] == dp[i][j]) {
          ++tmp;
        }
        if (tmp > maxsub) {
          maxsub = tmp;
        }
      }
    }
    return maxsub;
  };
  int count = backtrace(n, m);
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
