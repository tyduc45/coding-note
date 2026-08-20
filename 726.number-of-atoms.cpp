/*
 * @lc app=leetcode id=726 lang=cpp
 *
 * [726] Number of Atoms
 */
#include <vector>
#include <cctype>
#include <string>
#include <map>
using namespace std;
// @lc code=start
class Solution {
public:
    int where;

    void fill(map<string , int> &ans , string &name , map<string, int> &pre , int count)
    {
        if(name.length() > 0 || !pre.empty())
        {
            count = (count == 0) ? 1 : count;
            if(name.length() > 0)
            {
                string key = name;
                ans[key] += count;
            }
            else
            {
                vector<string> keys;
                for(const auto &pair : pre)
                {
                    keys.push_back(pair.first);
                }
                for(const string &key : keys)
                {
                    ans[key] += pre[key] * count;
                }
            }
        }
    }
    map<string , int> f(string &s , int i)
    {
        map<string , int> ans;
        string name;
        map<string , int> pre;
        int cnt = 0;
        while(i < s.length() && s[i] != ')')
        {
            if (s[i] >= 'A' && s[i] <= 'Z' || s[i] == '(')
            {
                fill(ans, name , pre, cnt);
                name.clear();
                pre.clear();
                cnt = 0;
                if(s[i] >= 'A' && s[i] <= 'Z')
                {
                    name += s[i++];
                }
                else // '('
                {
                    pre = f(s , i + 1);
                    i = where + 1;
                }
            }
            else if(s[i] >= 'a' && s[i] <= 'z')
            {
                name += s[i++];
            }
            else // digit 
            {
                cnt = 10 * cnt + s[i++] - '0';
            }
        }
        fill(ans, name, pre , cnt);
        where = i;
        return ans;
    }
    string countOfAtoms(string formula) {
        where = 0;
        map<string , int> result = f(formula , 0);
        string ans;
        vector<string> keys;
        for(const auto &pair : result)
        {
            keys.push_back(pair.first);
        }
        for(string key : keys)
        {
            ans += key;
            int count = result[key];
            if(count > 1)
            {
                ans += to_string(count);
            }
        }
        return ans;
    }
};
// @lc code=end

