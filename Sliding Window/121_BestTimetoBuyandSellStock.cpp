// Time Complexity: O(n)
// Space Complexity: O(1)
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int lowPrice = prices[0];
    int res{0};
    for (int i{1}; i < prices.size(); i++) {
      lowPrice = min(lowPrice, prices[i]);
      res = max(res, prices[i] - lowPrice);
    }
    return res;
  }
};
