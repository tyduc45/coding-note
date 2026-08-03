/*
 * @lc app=leetcode id=329 lang=cpp
 *
 * [329] Longest Increasing Path in a Matrix
 */

// @lc code=start
#include <climits>
class Solution {
public:
    int m;
    int n;
    vector<vector<int>> memo;

    int directions[4][2] = {
        {-1 , 0},
        {1,0},
        {0,-1},
        {0,1}
    };

    int dfs(vector<vector<int>> &matrix , int row , int col){
       if(memo[row][col] != 0) return memo[row][col];
       int longest = 1;
       // find longest increse of current position : row , col 
       for(const auto &direction : directions)
       {
          int next_row = row + direction[0];
          int next_col = col + direction[1];

          bool inside = next_row < m && next_row >= 0 
                        && next_col < n && next_col >= 0;
          if(!inside){ continue; }
          if(matrix[next_row][next_col] > matrix[row][col]){
            longest = max(longest ,1 + dfs(matrix , next_row , next_col));
          } 
       }
       // store the result of the search 
       memo[row][col] = longest;
       return longest;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
         m = matrix.size();
         n = matrix[0].size();

        memo.assign(m, vector<int>(n, 0));

        int ans = INT_MIN;
        for(int row = 0 ; row < m ; row++)
        {
            for(int col = 0 ; col < n ; col++)
            {   
                ans = max(ans , dfs(matrix, row , col));                
            }
        }
        return ans;
    }
};
// @lc code=end

