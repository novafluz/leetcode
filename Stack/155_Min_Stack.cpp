// Time Complexity: O(1)
// Space Complexity: O(n)
#include <algorithm>
#include <stack>
using namespace std;
class MinStack {
private:
  stack<int> stk;
  stack<int> minStack; // layer traverse down in ascending order
public:
  MinStack() {}

  void push(int val) {
    stk.push(val);
    val = (minStack.empty()) ? val : min(val, minStack.top());
    minStack.push(val);
  }
  void pop() {
    minStack.pop();
    stk.pop();
  }

  int top() { return stk.top(); }

  int getMin() { return minStack.top(); }
};
