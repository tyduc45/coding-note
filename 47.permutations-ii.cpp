/*
 * @lc app=leetcode id=47 lang=cpp
 *
 * [47] Permutations II
 */

// @lc code=start
#include <set>
#include <vector>
using namespace std;
class Solution {
public:
    void swap(vector<int> &nums, int i , int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
    void f(vector<int> &nums , int i , vector<vector<int>> &ans)
    {
        if(i == nums.size())
        {
            vector<int> cur;
            for(const auto &num :nums)
            {
                cur.push_back(num);
            }
            ans.push_back(cur);
        }
        else 
        {
            set<int> hash_set;
            for(int j = i; j < nums.size();j++)
            {
                if(hash_set.find(nums[j]) == hash_set.end())
                {
                    hash_set.insert(nums[j]);
                    swap(nums, i , j);
                    f(nums , i + 1 , ans);
                    swap(nums, i , j);
                }
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        f(nums , 0 , ans);
        return ans;
    }
};
// @lc code=end

