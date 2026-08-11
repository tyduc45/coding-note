// http://nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a
#include <set>
#include <string>
#include <vector>
using namespace std;
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @return string字符串vector
     */
    string turn_into_string(vector<char> &path , int size)
    {
        string builder = "";
        for(int i = 0 ; i < size ; i++)
        {
            builder += path[i];
        }
        return builder;
    }
    //vector<char> &path + int size 相当于string 
    void f(string &s , int i , vector<char> &path , int size , set<string> & set)
    {
        if(i == s.length())
        {
            string builder = turn_into_string(path, size);
            set.insert(builder);
        }
        else 
        {
            path[size] = s[i];
            f(s , i + 1 , path , size + 1 , set); // 要这个字符， 那么path的size + 1
            f(s , i + 1 , path , size , set);          // 不要这个字符， 那么path的size和之前一样
        }
    }
    vector<string> generatePermutation(string s) {
        // write code here
        vector<string> ans;
        int n = s.length();
        set<string> hash_set;
        vector<char> path(n , '0');
        f(s, 0 , path , 0 , hash_set);
        for(const auto & elem : hash_set)
        {
            ans.push_back(elem);
        }
        return ans;
    }
};