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
   static const int M = 105;
   static const int N = 105;
   bool visited[M][N];
   int queue[M * N][2];
   int l , r;
   int move[5] = {-1,0 , 1, 0 , -1};
   int maxDistance(vector<vector<int>> &grid)
   {
     int m = grid.size();
     int n = grid[0].size();
     l = r = 0;
     int seas = 0;
     for(int i = 0 ; i < m ; i++)
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
     if(seas == 0 || seas == m*n)
     {
        return -1;
     }
     int level = 0;
     while(l < r)
     {
        int size = r - l;
        for(int i = 0 ; i < size ; i++)
        {
            int x = queue[l][0];
            int y = queue[l++][1];

            for(int k = 0 ; k < 4 ; k++)
            {
                int nx = x + move[k];
                int ny = y + move[k + 1];
                if(nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    queue[r][0] = nx;
                    queue[r++][1] = ny;
                }
            }
        }
        level++;
     }
     return level - 1;
   }
};
// @lc code=end

