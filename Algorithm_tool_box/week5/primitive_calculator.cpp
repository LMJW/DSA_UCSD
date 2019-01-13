#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

struct dpelement {
  int value;
  int op;  // 0-> -1 operation; 1-> *2 operation; 2-> *3 operation
};

void threemin(int x, int y, int z, dpelement& p) {
  int idx, v;
  if (x > y) {
    v = y;
    idx = 1;
  } else {
    v = x;
    idx = 0;
  }
  if (v > z) {
    v = z;
    idx = 2;
  }
  p.value = v;
  p.op = idx;
};

vector<int> optimal_sequence(int n) {
  std::vector<dpelement> dp(n + 1);
  dp[0].value = -1;
  for (int i = 1; i < n + 1; ++i) {
    int minusone = dp[i - 1].value + 1;
    int twod, threed;
    if (i % 2 == 0) {
      twod = dp[i / 2].value + 1;
    } else {
      twod = dp[i - 1].value + 1;
    }

    if (i % 3 == 0) {
      threed = dp[i / 3].value + 1;
    } else {
      threed = dp[i - 1].value + 1;
    }
    threemin(minusone, twod, threed, dp[i]);
  }

  std::vector<int> res;
  int idx = n;
  int count = 0;

  while (idx > 1) {
    ++count;
    res.push_back(idx);
    switch (dp[idx].op) {
      case 0:
        --idx;
        break;
      case 1:
        idx /= 2;
        break;
      case 2:
        idx /= 3;
        break;
    }
  }
  res.push_back(1);

  std::reverse(res.begin(), res.end());
  return res;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
