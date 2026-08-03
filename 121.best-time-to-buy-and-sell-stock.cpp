/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 */

// @lc code=start
#include <climits>
#include <cmath>
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int dp = 0;
        int ans = 0;
        for(int i = 1 ; i < prices.size(); i++){
            int diff = prices[i] - prices[i - 1];
            dp = fmax(dp + diff, diff);
            ans = fmax(dp ,ans);
        }
        return ans;
    }
};
// @lc code=end

