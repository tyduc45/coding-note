/*
 * @lc app=leetcode id=1368 lang=cpp
 *
 * [1368] Minimum Cost to Make at Least One Valid Path in a Grid
 */

// @lc code=start
#include <vector>
#include <deque>
using namespace std;
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
       int m = grid.size();
       int n = grid[0].size();
       vector<vector<int>> directions = {
        {}, {0,1},{0,-1},
        {1,0}, {-1,0}
       };
       vector<vector<int>> distances(m , vector<int>(n , INT_MAX));
       deque<pair<int,int>> nodeStash;
       distances[0][0] = 0;
       nodeStash.push_front({0,0});
       while(!nodeStash.empty())
       {
          auto node = nodeStash.front();
          nodeStash.pop_front();
          int x = node.first;
          int y = node.second;
          if(x == m - 1 && y == n - 1)
          {
            return distances[x][y];
          }
          for(int i = 1; i < 5 ; i++)
          {
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            int weight = grid[x][y] != i ? 1 : 0;
            if(nx < m && nx >= 0 && ny < n && ny >= 0 &&
                distances[x][y] + weight < distances[nx][ny])
                {
                    distances[nx][ny] = distances[x][y] + weight;
                    if(weight == 1)
                    {
                        nodeStash.push_back({nx , ny});
                    }
                    else
                    {
                        nodeStash.push_front({nx , ny});
                    }
                }
          }
       }
       return -1;
    }
};
// @lc code=end

