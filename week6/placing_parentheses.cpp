#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using std::max;
using std::min;
using std::string;
using std::vector;

long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}
long long fourmax(long long& a, long long& b, long long& c, long long& d) {
    long long res = a;
    if (res < b) {
        res = b;
    }
    if (res < c) {
        res = c;
    }
    if (res < d) {
        res = d;
    }
    return res;
}

long long fourmin(long long& a, long long& b, long long& c, long long& d) {
    long long res = a;
    if (res > b) {
        res = b;
    }
    if (res > c) {
        res = c;
    }
    if (res > d) {
        res = d;
    }
    return res;
}

void tokenizeinput(const string& exp, vector<int>& nums, vector<char>& ops) {
    // Do I need to consider first negative number?
    // I don't think I need to consider this case
    for (int i = 0; i < exp.size(); ++i) {
        if (i % 2 == 0) {
            char e = exp[i];
            nums.push_back(e - '0');
        } else {
            ops.push_back(exp[i]);
        }
    }
    // for (auto e : nums) {
    //     std::cout << e << " ";
    // }

    // for (auto e : ops) {
    //     std::cout << e << " ";
    // }
}

long long get_maximum_value(const string& exp) {
    vector<int> nums;
    vector<char> ops;
    tokenizeinput(exp, nums, ops);

    int n = nums.size();
    vector<vector<long long>> dpmin(n, vector<long long>(n, 0));
    vector<vector<long long>> dpmax(n, vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; i + j < n; ++j) {
            if (i == 0) {
                dpmax[j][j + i] = nums[j];
                dpmin[j][j + i] = nums[j];
            } else if (i == 1) {
                dpmax[j][j + i] = eval(nums[j], nums[j + i], ops[j]);
                dpmin[j][j + i] = eval(nums[j], nums[j + i], ops[j]);
            } else {
                // dp[j][j+i] need (j,j+i-1) and (j+i,j+i)
                //
                long long vmax = std::numeric_limits<long long>::min();
                long long vmin = std::numeric_limits<long long>::max();
                long long t;
                for (int k = 0; k < i; ++k) {
                    t = eval(dpmax[j][j + k], dpmax[j + k + 1][j + i],
                             ops[j + k]);
                    if (t > vmax) {
                        vmax = t;
                    }
                    if (t < vmin) {
                        vmin = t;
                    }

                    t = eval(dpmin[j][j + k], dpmin[j + k + 1][j + i],
                             ops[j + k]);
                    if (t > vmax) {
                        vmax = t;
                    }
                    if (t < vmin) {
                        vmin = t;
                    }

                    t = eval(dpmax[j][j + k], dpmin[j + k + 1][j + i],
                             ops[j + k]);
                    if (t > vmax) {
                        vmax = t;
                    }
                    if (t < vmin) {
                        vmin = t;
                    }

                    t = eval(dpmin[j][j + k], dpmax[j + k + 1][j + i],
                             ops[j + k]);
                    if (t > vmax) {
                        vmax = t;
                    }
                    if (t < vmin) {
                        vmin = t;
                    }
                }
                dpmax[j][j + i] = vmax;
                dpmin[j][j + i] = vmin;
            }
        }
    }

    // for (auto ele : dpmax) {
    //     std::cout << "\n";
    //     for (auto e : ele) {
    //         std::cout << e << " ";
    //     }
    // }
    // std::cout << "\ndpmax";

    // for (auto ele : dpmin) {
    //     std::cout << "\n";
    //     for (auto e : ele) {
    //         std::cout << e << " ";
    //     }
    // }
    // std::cout << "\ndpmin";
    return dpmax[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
