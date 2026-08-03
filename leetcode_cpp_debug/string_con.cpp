#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n , k ;
        cin >> n >> k;
        
        if(k == n - 1){
            cout << -1 << "\n";
            continue;
        }
        int r = n - k;
        
        int zeroCount = (n + 1) / 2;
        int oneCount = n / 2;

        vector<int> runLength(r , 1);
        // 0|1|0
        int zero_fragment_count = (r + 1) / 2;
        int one_fragment_count = r / 2;
        runLength[0] += zeroCount - zero_fragment_count;
        runLength[1] += oneCount - one_fragment_count;

        string ans;
        for(int i = 0 ; i < r ; i++){
            char c = (i % 2) ? '0' : '1';
            ans += string(runLength[i] , c);
        }
        cout << ans << "\n";
    }
    return 0;
}