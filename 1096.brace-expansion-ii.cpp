/*
 * @lc app=leetcode id=1096 lang=cpp
 *
 * [1096] Brace Expansion II
 */

// @lc code=start
#include <set>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int where;
    // 需要分析清楚结算时刻， 并根据题目需求给出结算方法
    set<string> mul(const set<string> &a , const set<string> &b)
    {
        set<string> res;
        for(const string &x : a)
        {
            for(const string &y: b)
            {
                res.insert(x + y);
            }
        }
        return res;
    }
    set<string> f(string& s , int i)
    {
        set<string> cur = {""};
        set<string> ans;
        string str;
        while(i < s.length() && s[i] != '}')
        {
            if(s[i] >= 'a' && s[i] <= 'z')
            {
                str += s[i++];
            }
            else if(s[i] == ',') // 结算前面的
            {
                if(!str.empty())
                {
                    cur = mul(cur , {str});
                    str.clear();
                }
                ans.insert(cur.begin(), cur.end());
                cur = {""};
                i++;
            }
            else // '{'
            {
                if(!str.empty())
                {
                    cur = mul(cur , {str});
                    str.clear();
                }
                cur = mul(cur , f(s , i + 1));
                i = where + 1;
            }
        }
        if(!str.empty())
        {
            cur = mul(cur , {str});
        }
        ans.insert(cur.begin(), cur.end());
        where = i;
        return ans;
    }
    vector<string> braceExpansionII(string expression) {
        where = 0;
        set<string> result;
        result = f(expression , 0);
        vector<string> ans(result.begin() , result.end());
        return ans;
    }
};
// @lc code=end

