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
    const static int M = 105;
    const static int N = 105;
    int move[5] = {
        -1,0,1,0,-1
    };
    int queue[M * N][2];
    int l,r;
    bool visited[M][N];

    int maxDistance(vector<vector<int>>& grid) {
        l = r = 0;
        int m = grid.size();
        int n = grid[0].size();
        int seas = 0;
        for(int i = 0 ; i < m ;i++)
        {
            for(int j = 0 ; j < n ; j++)
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
        if(seas == 0 || seas == m * n)
        {
            return -1;
        }
        int level = 0;
        while(l < r)
        {
            level++;
            int size = r - l;
            for(int k = 0 ,x , y , nx , ny;k < size ;k++)
            {
                x = queue[l][0];
                y = queue[l++][1];
                for(int i = 0 ; i < 4;i++)
                {
                    nx = x + move[i];
                    ny = y + move[i + 1];
                    if(nx >= 0 && ny >= 0 && nx < m && ny < n && !visited[nx][ny])
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

