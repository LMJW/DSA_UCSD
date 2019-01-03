#include <cassert>
#include <iostream>
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
                long long t1;
                long long t2;
                long long t3;
                long long t4;
                long long t5;
                long long t6;
                long long t7;
                long long t8;
                long long vmax;
                long long vmin;
                t1 = eval(dpmax[j][j + i - 1], dpmax[j + i][j + i],
                          ops[j + i - 1]);
                t2 = eval(dpmax[j][j], dpmax[j + 1][j + i], ops[j]);

                t3 = eval(dpmin[j][j + i - 1], dpmin[j + i][j + i],
                          ops[j + i - 1]);
                t4 = eval(dpmin[j][j], dpmin[j + 1][j + i], ops[j]);

                t5 = eval(dpmax[j][j + i - 1], dpmin[j + i][j + i],
                          ops[j + i - 1]);
                t6 = eval(dpmax[j][j], dpmin[j + 1][j + i], ops[j]);

                t7 = eval(dpmin[j][j + i - 1], dpmax[j + i][j + i],
                          ops[j + i - 1]);
                t8 = eval(dpmin[j][j], dpmax[j + 1][j + i], ops[j]);

                vmax = fourmax(t1, t2, t3, t4);
                int tt = fourmax(t5, t6, t7, t8);
                if (vmax < tt) {
                    vmax = tt;
                }

                vmin = fourmin(t1, t2, t3, t4);
                tt = fourmin(t5, t6, t7, t8);
                if (vmin > tt) {
                    vmin = tt;
                }

                dpmax[j][j + i] = vmax;
                dpmin[j][j + i] = vmin;
            }
        }
    }

    for (auto ele : dpmax) {
        std::cout << "\n";
        for (auto e : ele) {
            std::cout << e << " ";
        }
    }
    std::cout << "\ndpmax";

    for (auto ele : dpmin) {
        std::cout << "\n";
        for (auto e : ele) {
            std::cout << e << " ";
        }
    }
    std::cout << "\ndpmin";
    return dpmax[0][n - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
