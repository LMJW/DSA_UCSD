#include <iostream>
#include <string>

using std::string;

// diagnal move: 0; vertical move: 1; horizontal move: 2;
int threemin(int diag, int y, int x, int& dir) {
  dir = 0;
  int v = diag;
  if (v > y) {
    dir = 1;
    v = y;
  }
  if (v > x) {
    dir = 2;
    v = x;
  }
  return v;
}

int edit_distance(const string& str1, const string& str2) {
  int n = str1.size();
  int m = str2.size();
  int dp[n + 1][m + 1];
  int count = 0;
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (i == 0) {
        dp[i][j] = j;
      } else if (j == 0) {
        dp[i][j] = i;
      } else {
        int dir;
        dp[i][j] = threemin(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1], dir);
        if (dir == 0 && str1[i - 1] == str2[j - 1]) {
          ;
        } else {
          ++dp[i][j];
        }
      }
    }
  }
  return dp[n][m];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
