/*
 * @lc app=leetcode id=42 lang=cpp
 *
 * [42] Trapping Rain Water
 */

// @lc code=start
#include <vector>
using namespace std;
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int l = 0;
        int r = height.size() - 1;
        int leftMax = height[l];
        int rightMax = height[r];
        while(l <= r)
        {
            if(leftMax <= rightMax)
            {
                ans += max(leftMax - height[l] , 0);
                leftMax = max(leftMax , height[l]);
                l++;
            }
            else 
            {
                ans += max(rightMax - height[r] , 0);
                rightMax = max(rightMax , height[r]);
                r--;
            }
        }
        return ans;
    }
};
// @lc code=end

