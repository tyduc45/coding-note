/*
 * @lc app=leetcode id=90 lang=cpp
 *
 * [90] Subsets II
 */

// @lc code=start
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    void f(vector<int> &nums , int i , vector<int> &path , set<vector<int>> &visited)
    {
        // 中止条件
        if(i == nums.size())
        {
            if(visited.find(path) == visited.end())
            {
                visited.insert(path);
            }
        }
        else 
        {
            path.push_back(nums[i]);
            f(nums, i + 1 , path, visited);
            path.pop_back();
            f(nums, i + 1 , path , visited);
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin() , nums.end());
        int n = nums.size();
        vector<vector<int>> ans;
        set<vector<int>> visited;
        vector<int> path(0);
        // 一个一个的向后找， 如果下一个等于上一个就直接跳过
        for(int i = 0 ; i < n;i++)
        {
            if(i >= 1 && nums[i] == nums[i - 1]) continue;
            f(nums , i , path ,visited);
        }
        for(const auto &path : visited)
        {
            ans.push_back(path);
        }
        return ans;
    }
};
// @lc code=end

