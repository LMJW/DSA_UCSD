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
    // use inorder traversal
    std::function<void(int)> f;
    vector<int> res;
    bool wrong = false;

    f = [&](int idx) {
        auto l = tree[idx].left;
        if (l != -1) {
            if (tree[l].key < tree[idx].key) {
                f(tree[idx].left);
            } else {
                wrong = true;
                return;
            }
        };

        res.push_back(tree[idx].key);
        if (tree[idx].right != -1) {
            f(tree[idx].right);
        };
    };

    if (tree.size() > 0) {
        f(0);
    };
    if (wrong) {
        return false;
    };
    for (int i = 1; i < res.size(); ++i) {
        if (res[i] < res[i - 1]) {
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
