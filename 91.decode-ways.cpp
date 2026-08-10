/*
 * @lc app=leetcode id=91 lang=cpp
 *
 * [91] Decode Ways
 */

// @lc code=start
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    int numDecodings(string s) {
        int n = s.length();
        vector<int> f(n + 1 , 0);
        f[0] = 1;
        for(int i = 1; i <= n ;i++)
        {
            if(s[i - 1] != '0')
            {
                f[i] += f[i - 1];
            }
            if(i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] -'0') <= 26))
            {
                f[i] += f[i - 2];
            }
        }
        return f[n];
    }
};
// @lc code=end

