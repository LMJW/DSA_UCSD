#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int>& a,
                                   vector<int>& b,
                                   size_t left,
                                   size_t right) {
    long long number_of_inversions = 0;
    if (right <= left + 1)
        return number_of_inversions;
    size_t ave = left + (right - left) / 2;
    number_of_inversions += get_number_of_inversions(a, b, left, ave);
    number_of_inversions += get_number_of_inversions(a, b, ave, right);

    int i = left;
    int j = ave;

    for (int k = 0; i + j - ave < right; ++k) {
        if (i < ave && j < right) {
            if (a[i] <= a[j]) {
                b[left + k] = a[i];
                ++i;
            } else {
                b[left + k] = a[j];
                ++j;
                number_of_inversions += (ave - i);
            }
        } else if (i < ave) {
            b[left + k] = a[i];
            ++i;
        } else {
            b[left + k] = a[j];
            ++j;
        }
    }
    // for (auto e : a) {
    //     std::cout << e << " ";
    // }
    // std::cout << " A\n";

    // for (auto e : b) {
    //     std::cout << e << " ";
    // }
    // std::cout << " b\n";
    // std::cout << number_of_inversions << " \n";
    // a = b;
    for (int i = left; i < right; ++i) {
        a[i] = b[i];
    }

    return number_of_inversions;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b(a.size());
    std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
