// Time Complexity: O(n)
// Space Complexity: O(n)
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;
class Solution {
public:
  bool isValid(string s) {
    stack<char> myStack;
    unordered_map<char, char> dict = {{')', '('}, {']', '['}, {'}', '{'}};

    for (char word : s) {
      if (dict.count(word)) {

        if (myStack.empty() || myStack.top() != dict[word]) {
          return false;
        }
        myStack.pop();
      } else {

        myStack.push(word);
      }
    }

    return myStack.empty();
  }
};