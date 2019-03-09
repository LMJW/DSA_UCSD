#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_)
        : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree) {
    // I will do an inorder tree traversal
    std::function<void(int)> f;
    vector<int> results;

    f = [&](int idx) {
        if (tree[idx].left != -1) {
            f(tree[idx].left);
        };
        results.push_back(tree[idx].key);
        if (tree[idx].right != -1) {
            f(tree[idx].right);
        };
    };

    if (tree.size() > 0) {
        f(0);
    }
    for (int i = 1; i < results.size(); ++i) {
        if (results[i] < results[i - 1]) {
            return false;
        };
    }

    return true;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
