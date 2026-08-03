/*
 * @lc app=leetcode id=797 lang=cpp
 *
 * [797] All Paths From Source to Target
 */

 #include <vector>
 #include <stack>
 #include <iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int target;
    vector<int> path;
    vector<vector<int>> ans;
    void dfs(vector<vector<int>>& graph , int currNode = 0){
        path.push_back(currNode);
        if(currNode == target) {
            ans.push_back(path);
        }
        else{
            for(const auto neightbor : graph[currNode]){
                dfs(graph, neightbor);
            }
        }
        path.pop_back();
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
       target = graph.size() - 1;
       dfs(graph);
       return ans;
    }
};

// @lc code=end

