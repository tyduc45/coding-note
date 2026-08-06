/*
 * @lc app=leetcode id=126 lang=cpp
 *
 * [126] Word Ladder II
 */

// @lc code=start
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
using namespace std;
class Solution {
public:
    unordered_set<string> dict;
    unordered_set<string> currLevel;
    unordered_set<string> nextLevel;
    unordered_map<string, vector<string>> gragh;
    vector<vector<string>> ans;
    list<string> path;
    void dfs(string word , string aim)
    {
        path.push_front(word);
        if(word == aim)
        {
            ans.push_back(vector<string>(path.begin() , path.end()));
        }
        else if(gragh.find(word) != gragh.end()) 
        {
            for(string next : gragh[word])
            {
                dfs(next , aim);
            }
        }
        path.pop_front();
    }
    bool bfs(string begin ,string end)
    {
        bool find = false;
        currLevel.insert(begin);
        while(!currLevel.empty())
        {
            for(const auto & key : currLevel)
            {
                dict.erase(key);
            }
            for(string word : currLevel)
            {
                for(int i = 0 ; i < word.length() ;i++)
                {
                    string str = word;
                    for(char ch = 'a' ; ch <= 'z';ch++)
                    {
                        str[i] = ch;
                        if(dict.find(str) != dict.end() && str != word)
                        {
                            if(str == end)
                            {
                                find = true;
                            }
                            gragh[str].push_back(word);
                            nextLevel.insert(str);
                        }
                    }
                }
            }
            if(find)
            {
                return true;
            }
            else
            {
                unordered_set<string> temp = currLevel;
                currLevel = nextLevel;
                nextLevel = temp;
                nextLevel.clear();
            }
        }
        return false;
    }
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        for(const auto str : wordList)
        {
            dict.insert(str);
        }
        if(dict.find(endWord) == dict.end())
        {
            return ans;
        }
        if(bfs(beginWord , endWord))
        {
            dfs(endWord , beginWord);
        }
        return ans;
    }
};
// @lc code=end

