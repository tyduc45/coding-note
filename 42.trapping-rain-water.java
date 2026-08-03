/*
 * @lc app=leetcode id=42 lang=java
 *
 * [42] Trapping Rain Water
 */

// @lc code=start
class Solution {
    public int trap(int[] height) {
        int n = height.length;
        int left_max = height[0];
        int right_max = height[n - 1];
        int left = 0;
        int right = n - 1;
        int res = 0;
        while(left <= right){
            if(left_max < right_max)
            {
                res += Math.max(left_max - height[left] ,0);
                left_max = Math.max(left_max , height[left]);
                left++;
            }
            else
            {
                res += Math.max(right_max - height[right] , 0);
                right_max = Math.max(right_max , height[right]);
                right--;
            }
        }
        System.gc();
        return res;
    }
}
// @lc code=end

