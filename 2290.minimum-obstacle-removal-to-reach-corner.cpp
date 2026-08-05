/*
 * @lc app=leetcode id=2290 lang=cpp
 *
 * [2290] Minimum Obstacle Removal to Reach Corner
 */

// @lc code=start
#include <climits>
#include <vector>
#include <deque>
using namespace std;
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int move[5] = {-1,0,1,0,-1};
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> distance(
            m , vector<int>(n , INT_MAX)
        );
        deque<pair<int,int>> nodeStash;
        distance[0][0] = 0;
        nodeStash.push_front({0,0});
        while(!nodeStash.empty())
        {
            auto node = nodeStash.front();
            nodeStash.pop_front();
            int x = node.first;
            int y = node.second;
            if(x == m - 1 && y == n - 1)
            {
                return distance[x][y];
            }

            for(int i = 0 ; i < 4;i++)
            {
                int nx = x + move[i];
                int ny = y + move[i + 1];
                if(nx >= 0 && nx < m && ny >= 0 && ny < n &&
                   distance[x][y] + grid[nx][ny] < distance[nx][ny])
                 {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    if(grid[nx][ny] == 0)
                    {
                        nodeStash.push_front({nx , ny});
                    }
                    else
                    {
                        nodeStash.push_back({nx , ny});
                    }
                 }
            }
        }
        return -1;
    }
};
// @lc code=end

