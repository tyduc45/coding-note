//https://www.nowcoder.com/practice/c215ba61c8b1443b996351df929dc4d4
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    int where = 0;
    //calculate s[i ...]
    int f(string &s, int i)
    {
        int cur = 0;
        vector<int> numbers;
        vector<char> ops;
        while(i < s.length() && s[i] != ')')
        {
            if(s[i] >= '0' && s[i] <= '9')
            {
                cur = 10 * cur + (s[i++] - '0');
            }
            else if(s[i] != '(')  // + - * /
            {
                push(numbers, ops , cur , s[i++]);
                cur = 0;
            }
            else // "(" 
            {
                cur = f(s , i + 1);
                i = where + 1; 
            }
        }
        push(numbers , ops , cur , '+');
        where = i;
        return compute(numbers, ops);
    }
    void push(vector<int> &numbers , vector<char> &ops , int cur, char op)
    {
        int n = numbers.size();
        if(n == 0 || ops[n - 1] == '+' || ops[n - 1] == '-')
        {
            numbers.push_back(cur);
            ops.push_back(op);
        }
        else 
        {
            if(ops[n - 1] == '*')
            {
                numbers[n - 1] *= cur;
            }
            else 
            {
                numbers[n - 1] /= cur;
            }
            ops[n - 1] = op;
        }
    }

    int compute(vector<int> numbers , vector<char> ops)
    {
        int ans = numbers[0];
        for(int i = 1; i < numbers.size();i++)
        {
            ans += ops[i - 1] == '+'? numbers[i] : -numbers[i];
        }
        return ans;
    }
    int solve(string s) {
        where = 0;
        return f(s , 0);
    }
};