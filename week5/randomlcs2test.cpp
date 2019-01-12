#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "lcs2_copy.h"

using std::vector;

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
        int n = rand() % 5 + 1;
        vector<int> a(0);
        for (int i = 0; i < n; i++) {
            a.push_back(rand() % n);
        }
        int m = rand() % 5 + 1;
        vector<int> b(0);
        for (int i = 0; i < m; i++) {
            b.push_back(rand() % m);
        }

        int v = lcs2(a, b);
        int v2 = longestCommonSubsequece(a, b);
        std::cout << count << " " << n << " " << m << " :" << v << v2
                  << std::endl;

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
