/*
 * @lc app=leetcode id=127 lang=cpp
 *
 * [127] Word Ladder
 */

// @lc code=start
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int ans = 0;
    unordered_set<string> dict;
    unordered_set<string> currLevel;
    unordered_set<string> nextLevel;
    bool bfs(string begin , string end)
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
                    for(char ch = 'a' ; ch <= 'z' ; ch++)
                    {
                        str[i] = ch;
                        if(dict.find(str) != dict.end() && str != word)
                        {
                            if(str == end)
                            {
                                find = true;
                            }
                            nextLevel.insert(str);
                        }
                    }
                }
            }
            if(nextLevel.size() != 0) 
            {
               ans++;
            }
            if(find)
            {
                return true;
            }
            currLevel.swap(nextLevel);
            nextLevel.clear();
        }
        return false;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        for(const auto &word : wordList)
        {
            dict.insert(word);
        }
        if(dict.find(endWord) == dict.end())
        {
            return ans;
        }
        int found = bfs(beginWord , endWord);
        return !found ? 0 : ans + 1;
    }
};
// @lc code=end

