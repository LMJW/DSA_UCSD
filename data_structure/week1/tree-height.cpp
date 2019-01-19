#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
   public:
    int key;
    Node* parent;
    std::vector<Node*> children;

    Node() { this->parent = NULL; }

    void setParent(Node* theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int recdepth(Node* n) {
    int max = 0;
    for (auto e : n->children) {
        int t = recdepth(e);
        if (max < t) {
            max = t;
        }
    }
    return 1 + max;
};

int getdepth(Node* n) {
    std::stack<Node*> st;
    std::stack<int> v;
    st.push(n);
    v.push(1);
    int maxheight = 1;
    while (!st.empty()) {
        auto t = st.top();
        st.pop();
        int l = v.top();
        v.pop();
        if (t->children.size() > 0) {
            for (auto c : t->children) {
                st.push(c);
                v.push(l + 1);
            }
        }
        if (maxheight < l) {
            maxheight = l;
        }
    }
    return maxheight;
}

int main_with_large_stack_space() {
    std::ios_base::sync_with_stdio(0);
    int n;
    std::cin >> n;

    std::vector<Node> nodes;
    nodes.resize(n);
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        std::cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        nodes[child_index].key = child_index;
    }

    // Replace this code with a faster implementation
    int maxHeight = 0;
    for (auto n : nodes) {
        if (n.parent == NULL) {
            maxHeight = getdepth(&n);
            break;
        }
    }

    std::cout << maxHeight << std::endl;
    return 0;
}

int main(int argc, char** argv) {
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;  // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                std::cerr << "setrlimit returned result = " << result
                          << std::endl;
            }
        }
    }

#endif
    return main_with_large_stack_space();
}
