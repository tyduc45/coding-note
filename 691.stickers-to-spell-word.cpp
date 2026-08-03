/*
 * @lc app=leetcode id=691 lang=cpp
 *
 * [691] Stickers to Spell Word
 */
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    static const int MAXN = 401;
    string queue[MAXN];
    int l , r;
    vector<vector<string>> graph;
    unordered_set<string> visited;
    Solution():graph(26)
    {
        // graph = { {size = 0, capa = 0 , data = nullptr},{ same }, ... }
        //  graph.size = 26 graph.capa = 32; data = &graph[0];
    }
    string nextFunc(string t , string s)
    {
        string builder;
        builder.reserve(max(s.length(),t.length()));
        for(int i = 0 , j = 0; i < t.length();)
        {
            if(j == s.length())
            {
                builder += t[i++];
            }
            else
            {
                if(t[i] < s[j])
                {
                    builder += t[i++];
                }
                else if(t[i] > s[j])
                {
                    j++;
                }
                else 
                {
                    i++;
                    j++;
                }
            }
        }
        return builder;
    }
   
    int minStickers(vector<string>& stickers, string target) {
        // 贴纸建图
        for(string str : stickers)
        {
            sort(str.begin() , str.end());
            for(int i = 0; i < str.length() ; i++) //逐字符考察
            {
                //如果发现他能搞定a，同时搞定b， 也能搞定c....，分别进入a b c邻接表
               if(i == 0 || str[i] != str[i - 1]) // 不重复加，如aabd ，不用往a里面加两次
               {
                  graph[str[i] - 'a'].push_back(str);
               } 
            }
        }
        sort(target.begin() , target.end());
        visited.insert(target);
        l = r = 0;
        queue[r++] = target; // 目标入队
        int level = 1;
        while(l < r)
        {
            int size = r - l;
            for(int i = 0 ; i < size ; i++)
            {
                string curr = queue[l++];
                for(string s : graph[curr[0] - 'a']) // 扩展所有能干掉当前手字符的字符串（优先挑选能干掉前缀的，剪枝体现在这里）
                {
                    string next = nextFunc(curr , s);
                    if(next == "")
                    {
                        return level;
                    }
                    else if(visited.find(next) == visited.end())
                    {
                        visited.insert(next);
                        queue[r++] = next;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};
// @lc code=end

