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
        dp[i][j] = threemin(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j], dir);
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

int longestCommonSubsequece(vector<int>& a, vector<int>& b) {
  int i, j;
  int len1 = a.size();
  int len2 = b.size();
  // create a matrix of order (len1+1)*(len2+1) to tabulate values
  int LCS[len1 + 1][len2 + 1];

  // LCS[i][j]=Length of longest common subsequence of str1[0....(i-1)] and
  // str2[0...(j-1)]

  // initializing
  for (i = 0; i <= len1; i++)
    LCS[i][0] = 0;  // empty str2

  for (j = 0; j <= len2; j++)
    LCS[0][j] = 0;  // empty str1

  // now, start filling the matrix row wise
  for (i = 1; i <= len1; i++) {
    for (j = 1; j <= len2; j++) {
      // if current character of both strings match
      if (a[i - 1] == b[j - 1]) {
        LCS[i][j] = 1 + LCS[i - 1][j - 1];
      }

      // mismatch
      else {
        LCS[i][j] = std::max(LCS[i - 1][j], LCS[i][j - 1]);
      }
    }
  }

  // now, return the final value
  return LCS[len1][len2];
}

void testalgos() {
  for (int count = 0; count < 10000; ++count) {
    int n = rand() % 20 + 1;
    vector<int> a(0);
    for (int i = 0; i < n; i++) {
      a.push_back(rand() % n);
    }
    int m = rand() % 20 + 1;
    vector<int> b(0);
    for (int i = 0; i < m; i++) {
      b.push_back(rand() % m);
    }

    int v = lcs2(a, b);
    int v2 = lcs2(a, b);
    std::cout << count << " " << n << " " << m << " :" << v << v2 << std::endl;

    if (v != v2) {
      std::cout << "\n\n";
      std::cout << "v: " << v << " | "
                << "v2: " << v2 << "\n";
      std::cout << "a :";
      for (auto e : a) {
        std::cout << e << " ";
      }
      std::cout << " \n";

      std::cout << "b :";
      for (auto e : b) {
        std::cout << e << " ";
      }
      std::cout << " \n";
      break;
    }
    // usleep(1000);
  }
}

int main() {
  // size_t n;
  // std::cin >> n;
  // vector<int> a(n);
  // for (size_t i = 0; i < n; i++) {
  //   std::cin >> a[i];
  // }

  // size_t m;
  // std::cin >> m;
  // vector<int> b(m);
  // for (size_t i = 0; i < m; i++) {
  //   std::cin >> b[i];
  // }

  // std::cout << lcs2(a, b) << std::endl;

  testalgos();
  std::cout << "\n DONE!" << std::endl;
}
