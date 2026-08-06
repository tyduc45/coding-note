/*
 * @lc app=leetcode id=407 lang=cpp
 *
 * [407] Trapping Rain Water II
 */

// @lc code=start
#include <vector>
#include <array>
#include <queue>
using namespace std;
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int move[5] = {-1,0,1,0,-1};
        int m = heightMap.size();
        int n = heightMap[0].size();
        vector<vector<bool>> visited(m , vector<bool>(n ,false));
        auto cmp = [](array<int, 3> a,array<int, 3> b){ return a[2] > b[2]; };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> minHeap(cmp);
        for(int i = 0 ; i < m ;i++)
        {
            for(int j = 0 ; j < n ;j++)
            {
                if(i == 0 || i == m - 1 || j == 0 || j == n - 1)
                {
                    visited[i][j] = true;
                    minHeap.push({i , j , heightMap[i][j]});
                }
            }
        }
        int ans = 0;
        while(!minHeap.empty())
        {
            auto node = minHeap.top();
            minHeap.pop();
            int x = node[0];
            int y = node[1];
            int w = node[2];
            ans += w - heightMap[x][y];
            for(int i = 0 ; i < 4 ; i++)
            {
                int nx = x + move[i];
                int ny = y + move[i + 1];
                if (ny >= 0 && ny < n && nx >= 0 && nx < m && !visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    minHeap.push({nx , ny , max(heightMap[nx][ny], w)});
                }
            }
        }
        return ans;
    }
};
// @lc code=end

