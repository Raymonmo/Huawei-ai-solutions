#include <bits/stdc++.h>
#include <climits>
#include <iostream>
#include <string>
using namespace std;

int main(){
    string text;
    if(!(cin>>text)) return 0;
    int n;
    cin>>n;
    vector<string> word(n);
    vector<int> score(n);
    for(int i = 0; i < n; i++){
        cin>>word[i]>>score[i];
    } 
    int m;
    cin>>m;
    vector<vector<string>> transfer(m, vector<string> (2));
    vector<int> score2(m);
    for(int i = 0; i < m; i++){
        cin>>transfer[i][0]>>transfer[i][1]>>score2[i];
    }
    vector<vector<bool>> visited(text.length() + 1, vector<bool> (n, false));
    vector<vector<int>> dp(text.length() + 1, vector<int> (n, INT_MIN / 2));

    for(int i = 1; i <= text.length(); i++){
        for(int k = 0; k < word.size(); k++){
            string c = word[k];
            int j = 0;
            while((i-1+j < text.length()) && (j < c.length()) && text[i-1+j] == c[j]){
                j++;
            }
            if(j == c.length()){
                if(i == 1) {
                    dp[i+j-1][k] = score[k];
                    visited[i+j-1][k] = 1;
                } else {
                    for(int d = 0; d < word.size(); d++){
                        if(visited[i-1][d] == true){
                            int trans_score = 0;
                            string pre = word[d];
                            for(int a = 0; a < m; a++){
                                if(pre == transfer[a][0] && c == transfer[a][1]){
                                    trans_score = score2[a];
                                }
                            }
                            int now_score = score[k] + trans_score;
                            dp[i+j-1][k] = max(dp[i+j-1][k], dp[i-1][d] + now_score);
                            visited[i+j-1][k] = true;
                        }
                    }
                }
                // cout<<i<<j<<endl;
                // cout<<i+j-1<<endl;
                // cout<<dp[i+j-1]<<endl;
            }
        }
    }
    int ans = INT_MIN;
    for(int d = 0; d < n; d++){
        ans = max(ans, dp[text.length()][d]);
    }
    if (ans < INT_MIN / 4) {
        cout << 0 << endl; 
    } else {
        cout << ans << endl;
    }
    return 0;
}