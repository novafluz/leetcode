// Time Complexity: O(n)
//  Space Complexity: O(1)

#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    int i{0};
    int j = numbers.size() - 1;
    while (i < j) {
      int curSum = numbers[i] + numbers[j];
      if (target == curSum) {
        return {i + 1, j + 1};
      } else if (target > curSum) {
        i++;
      } else {
        j--;
      }
    }
    return {};
  }
};
