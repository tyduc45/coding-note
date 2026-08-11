// http://nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a


/*
    我要找所有子串， 面对s中的一个字符， 我要么要他， 要么不要他，针对两种情况分别递归的搜索就可以了
*/
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
     // i代表当前处理了s中的几个字符，无论你要还是不要， 只要是做了决策，就是一次处理
    void f(string &s , int i , string &path , set<string> &visited)
    {
        if(i == s.length()) // s中的字符全部遍历完了，那么就去重的加入visited
        {
            if(visited.find(path) == visited.end())
            {
                visited.insert(path);
            }
        }
        else 
        {
            path += s[i];  // 要么要这个字符
            f(s , i + 1 , path , visited);
            path.erase(path.length() - 1 , 1); // 要么不要这个字符
            f(s, i + 1 , path , visited);
        }
    }
    vector<string> generatePermutation(string s) {
        int n = s.length();
        set<string> hash_set;
        vector<string> ans;
        string path;
        f(s , 0 , path, hash_set);
        for(string elem : hash_set)
        {
            ans.push_back(elem);
        }
        return ans;
    }
};