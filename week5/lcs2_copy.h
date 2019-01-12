#ifndef LCS2_COPY_H  // To make sure you don't declare the function more than
                     // once by including the header multiple times.
#define LCS2_COPY_H
#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

int lcs2(std::vector<int>&, std::vector<int>&);

#endif