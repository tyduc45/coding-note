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
    static const int MAXN = 403;
    string queue[MAXN];
    vector<vector<string>> graph;
    unordered_set<string> visited;
    Solution():graph(26){}
    int l , r;

    // s 干掉 t
    string nextFunc(string t , string s)
    {
        string builder;
        builder.reserve(max(t.length() , s.length()));
        for(int i = 0, j = 0 ; i < t.length();)
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
                    i++; j++;
                }
            }
        }
        return builder;
    }

    int minStickers(vector<string>& stickers, string target) {
        // char 建图
        for(string str : stickers)
        {
            // 逐字符检查当前sticker能干掉那些字符
            for(int i = 0 ; i < str.length() ; i++)
            {
                sort(str.begin() , str.end());
                if(i == 0 || str[i] != str[i - 1])
                {
                     graph[str[i] - 'a'].push_back(str);
                }
            }
        }
        l = r = 0;
        int level = 0;
        //对于当前目标开始bfs, target入队
        sort(target.begin() , target.end());
        queue[r++] = target;
        visited.insert(target);

        //bfs
        while(l < r)
        {
            level++;
            int size = r - l;
            for(int i = 0 ; i < size;i++)
            {
                string curr = queue[l++];
                sort(curr.begin() , curr.end());
                for(string s : graph[curr[0] - 'a'])
                {
                    string next = nextFunc(curr, s);
                    if(next == "")
                    {
                        return level;
                    }
                    if(visited.find(next) == visited.end())
                    {
                        visited.insert(next);
                        queue[r++] = next;
                    }
                }
            }
        }
        return -1;
    }
};
// @lc code=end

