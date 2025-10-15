#include <bits/stdc++.h>
#include <vector>
using namespace std;

int ans = 0;

int main(){
    int H,W,K1,K2;
    cin>>H>>W>>K1>>K2;
    vector<vector<int>> figure(H, vector<int> (W));
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            cin>>figure[i][j];
        }
    }
    vector<vector<int>> policy(K1, vector<int> (K2));
    for(int i = 0; i < K1; i++){
        for(int j = 0; j < K2; j++){
            cin>>policy[i][j];
        }
    }
    vector<vector<int>> energy(H, vector<int> (W));
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            int center = K1 / 2;
            int sum = 0;
            for(int dx = 0; dx < K1; dx++){
                for(int dy = 0; dy < K2; dy++){
                    int nx = i + dx - center;
                    int ny = j + dy - center;
                    if(nx >= 0 && nx < H && ny >= 0 && ny < W){
                        sum += policy[dx][dy] * figure[nx][ny];
                    }
                }
            }
            energy[i][j] = sum;
        }
    }
    vector<vector<int>> dp(H, vector<int> (W));
    for(int i = 0; i < H; i++){
        dp[i][0] = energy[i][0];
    }
    for(int j = 1; j < W; j++){
        for(int i = 0; i < H; i++){
            int maxpre = dp[i][j-1];
            if(i > 0){
                maxpre = max(maxpre, dp[i-1][j-1]);
            }
            if(i < H - 1){
                maxpre = max(maxpre, dp[i+1][j-1]);
            }
            dp[i][j] = maxpre + energy[i][j];
        }
    }
    for(int i = 0; i < H; i++){
        ans = max(ans, dp[i][W-1]);
    }
    double answer = double(ans);

    cout<<fixed<<setprecision(1)<<answer;

    return 0;
}