/*
 * @lc app=leetcode id=394 lang=cpp
 *
 * [394] Decode String
 */

// @lc code=start
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    int where;
    // string f(string &s , int i)
    // {
    //     string rpt = "";
    //     int cur = 0;
    //     vector<int> numbers;
    //     vector<string> rpts; // 用于存储将会重复出现的字符串/字符
    //     while(i < s.length() && s[i] != ']')
    //     {
    //         if(s[i] >= '0' && s[i] <= '9')
    //         {
    //             cur = 10 * cur + (s[i++] - '0');
    //         }
    //         else if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) 
    //         {
    //             rpt += s[i++];
    //         }
    //         else // 遇到 [
    //         {
    //             numbers.push_back(cur);
    //             rpts.push_back(f(s , i + 1));
    //             cur = 0;
    //             i = where + 1;
    //         }
    //     }
        
    //     where = i;
    //     return compute(numbers , rpts);
    // }
    string f(string& s, int i)
{
    string rpt = "";
    int cur = 0;

    vector<int> numbers;
    vector<string> rpts;

    while (i < s.length() && s[i] != ']')
    {
        if (isdigit(s[i]))
        {
            // 数字意味着上一段普通字符串结束
            if (!rpt.empty())
            {
                numbers.push_back(1);
                rpts.push_back(rpt);
                rpt.clear();
            }

            cur = cur * 10 + (s[i] - '0');
            i++;
        }
        else if (isalpha(s[i]))
        {
            rpt += s[i];
            i++;
        }
        else // 遇到 '['
        {
            numbers.push_back(cur);
            rpts.push_back(f(s, i + 1));

            cur = 0;
            i = where + 1;
        }
    }

    // 遇到 ] 或字符串末尾，提交最后一段普通字符串
    if (!rpt.empty())
    {
        numbers.push_back(1);
        rpts.push_back(rpt);
    }

    where = i;
    return compute(numbers, rpts);
}
    string compute(vector<int> &numbers , vector<string> &rpts)
    {
        int n = numbers.size();
        int m = rpts.size();
        int i;
        string ans = "";
        for(i = 0; i < n;i++)
        {
            for(int j = 0 ; j < numbers[i] ; j++)
            {
                ans += rpts[i];
            }
        }
        //把剩下的加上去
        for(int k = i + 1 ; k < m ;k++)
        {
            ans += rpts[k];
        }
        return ans;
    }
    string decodeString(string s) {
        where = 0;
        return f(s , 0);
    }
};
// @lc code=end

