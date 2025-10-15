#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
int main(){
    string text;
    getline(cin, text);
    int len = text.length();
    int n;
    cin>>n;
    vector<string> word1(n);
    vector<int> score1(n);
    unordered_map<string, int> q_score;
    unordered_map<string, int> query;
    for(int i = 0; i < n; i++){
        cin>>word1[i]>>score1[i];
        query[word1[i]] = i;
        q_score[word1[i]] = score1[i];
    }
    int m;
    cin>>m;
    vector<vector<string>> word2(m, vector<string>(2));
    vector<int> score2(m);
    for(int i = 0; i < m; i++){
        string w1, w2;
        int score;
        cin>>w1>>w2>>score;
        word2[i][0] = w1;
        word2[i][1] = w2;
        score2[i] = score;
    }
    
    vector<vector<int>> dp(len+1, vector<int> (n,-1000000));
    vector<vector<int>> visited(len+1, vector<int> (n,0));
    for(int i = 0; i < n; i++) dp[0][i] = 0;
    for(int i = 1; i <= len; i++){
        for(string c : word1){
            int j = 0;
            for(j = 0; j < c.size(); j++){
                if(i+j-1 >= len || text[i+j-1] != c[j]) break;
            }
            if(j == c.size() && i+j-1 <= len) {
                if(i-1 == 0) dp[i+j-1][query[c]] = q_score[c];
                else {
                    for(int k = 0; k < n; k++){
                        if(visited[i-1][k]){
                            int dif = 0;
                            for(int u = 0; u < m; u++){
                                if(word1[k] == word2[u][0] && c == word2[u][1]){
                                    dif = score2[u];
                                    break;
                                }
                            }
                            dp[i+j-1][query[c]] = max(q_score[c] + dp[i-1][k] + dif, dp[i+j-1][query[c]]);
                        }
                    }
                }
                visited[i+j-1][query[c]] = 1;
            }
        }
    }
    int ans = -1000000;
    for(int i = 0; i < n; i++){
        ans = max(ans, dp[len][i]);
    }
    ans = ans == -1000000 ? 0 : ans;
    cout<<ans;

    return 0;
}