// Time & Space Complexity: O(n)
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
class Solution {
public:
  bool containsDuplicate(vector<int> &nums) {
    unordered_set<int> hashmap;
    for (int e : nums) {
      if (hashmap.find(e) != hashmap.end())
        return true;
      hashmap.insert(e);
    }
    return false;
  }
};