#include <iostream>
#include <stdio.h>
#include <array>

/*   https://www.nowcoder.com/practice/d88ef50f8dab4850be8cd4b95514bbbd
3
3 100
10 20
45 89
5 40
3 100
10 20
45 90
5 40
3 100
10 20
45 84
5 40
*/

using namespace std;
const int maxn = 11;
array<int , maxn> damage;
array<int , maxn> double_trigger_blood;

void swap(int i , int j)
{
    int temp0 = damage[i];
    damage[i] = damage[j];
    damage[j] = temp0;
    int temp1 = double_trigger_blood[i];
    double_trigger_blood[i] = double_trigger_blood[j];
    double_trigger_blood[j] = temp1;
}

int f(int n ,int i , int r)
{
    if(r <= 0)
    {
        return i;
    }
    if(i == n)
    {
        return INT_MAX;
    }
    int ans = INT_MAX;
    for(int j = i; j < n ; j++)
    {
        swap(i , j);
        ans = min(ans , f(n , i + 1 , r - (r > double_trigger_blood[i] ? damage[i]:damage[i] * 2)));
        swap(i , j);
    }
    return ans;
}

int main() {
    int T;
    cin >> T;
    int m , n;
    int ans = INT_MAX;
    
    while(T--)
    {
        cin >> n >> m;
        for(int i = 0 ; i < n ;i++)
        {
            cin >> damage[i];
            cin >> double_trigger_blood[i];
        }
        ans = f(n,0,m);
        printf("%d\n" , (ans == INT_MAX ? -1: ans));
    }
}
// 64 位输出请用 printf("%lld")