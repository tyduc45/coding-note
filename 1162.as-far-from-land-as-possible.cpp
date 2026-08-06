/*
 * @lc app=leetcode id=1162 lang=cpp
 *
 * [1162] As Far from Land as Possible
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
   const static int N = 105;
   const static int M = 105;
   int queue[M * N][2];
   bool visited[M][N];
   int move[5] = {-1,0,1,0,-1};
   int maxDistance(vector<vector<int>> &grid)
   {
     int l = 0; 
     int r = 0;
     int m = grid.size(); 
     int n = grid[0].size();
     int seas = 0;
     for(int i = 0 ; i < m ;i++)
     {
        for(int j = 0 ; j < n ;j++)
        {
            if(grid[i][j] == 1)
            {
                visited[i][j] = true;
                queue[r][0] = i;
                queue[r++][1] = j;
            }
            else 
            {
                visited[i][j] = false;
                seas++;
            }
        }
     }
     if(seas == m * n || seas == 0)
     {
        return -1;
     }
     int level = 0;
     while(l < r)
     {
        level++;
        int size = r - l;
        for(int i = 0 ; i < size;i++)
        {
            int x = queue[l][0];            
            int y = queue[l++][1];
            for(int k = 0 ; k < 4;k++)
            {
                int nx = x + move[k];
                int ny = y + move[k + 1];
                if(nx < m && nx >= 0 && ny < n && ny >= 0 && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    queue[r][0] = nx;
                    queue[r++][1] = ny;
                }
            }
        }
     }
     return level - 1;
   }
};
// @lc code=end

