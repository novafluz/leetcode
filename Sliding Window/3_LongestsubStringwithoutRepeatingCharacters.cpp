// Time Complexity: O(n)
// Space Complexity: O(n)
#include <string>
#include <unordered_set>
using namespace std;
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int l{0}, r{0}, cnt{0};
    unordered_set<char> store;
    while (r < s.size()) {
      if (store.find(s[r]) == store.end()) {
        store.insert(s[r]);
        cnt = max(cnt, r - l + 1);
        r++;
      } else {
        store.erase(s[l]);
        l++;
      }
    }
    return cnt;
  }
};
