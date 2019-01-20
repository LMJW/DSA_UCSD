#include <iostream>
#include <stack>
#include <vector>
using std::stack;
using std::vector;

class MaxStack {
public:
    MaxStack(){};
    void push(int ele) {
        if (num.empty()) {
            num.push(ele);
            maxstack.push(ele);
        } else {
            int t = maxstack.top();
            num.push(ele);
            if (ele > t) {
                maxstack.push(ele);
            } else {
                maxstack.push(t);
            }
        }
    };
    void pop() {
        num.pop();
        maxstack.pop();
    };
    int max() { return maxstack.top(); };

private:
    stack<int> num;
    stack<int> maxstack;
};

int main() {
    int n;
    std::cin >> n;

    // init mystack
    MaxStack ms = MaxStack();
    // get input from stdin
    for (int i = 0; i < n; ++i) {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "push") {
            int num;
            std::cin >> num;
            ms.push(num);
        } else if (cmd == "pop") {
            ms.pop();
        } else {
            std::cout << ms.max() << "\n";
        }
    }

    return 0;
}