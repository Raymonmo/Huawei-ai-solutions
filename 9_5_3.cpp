#include <bits/stdc++.h>
#include <cmath>
using namespace std;

int main(){
    int n;
    cin>>n;
    int s,x,k;
    cin>>s>>x>>k;
    vector<vector<double>> p(n + 1, vector<double> (n + 1));
    for(int n1 = 1; n1 <= n; n1++){
        for(int n2 = 1; n2 <= n; n2++){
            cin>>p[n1][n2];
        }
    }   

    // backtrack(p, s, x, 0, k);
    vector<vector<double>> dp(k+1, vector<double> (n+1,0));
    dp[0][s] = 1;
    double ans = 0;
    for(int i = 1; i <= k; i++){
        for(int j = 1; j <= n; j++){
            if(j == x) dp[i][j] = 0;
            else {
                for(int u = 1; u <= n; u++){
                    dp[i][j] += dp[i-1][u] * p[u][j];
                }
            }
            if(i == k){
                ans += dp[i][j];
            }
        }
    }

    ans = round(1000000 * ans) / 1000000;
    cout<<fixed<<setprecision(6)<<ans;
    return 0;
}