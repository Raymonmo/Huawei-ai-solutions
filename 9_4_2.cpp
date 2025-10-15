#include <atomic>
#include <bits/stdc++.h>
#include <queue>
using namespace std;

int main(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    vector<long long> length(m);
    for(int i = 0; i < m; i++){
        cin>>length[i];
    }
    long long ans = 0;
    sort(length.begin(),length.end(), greater<int>());
    priority_queue<long long, vector<long long>, greater<long long>> q;
    for(int i = 0; i < n; i++) q.push(0);
    for(auto c : length){
        long long cur = q.top();
        q.pop();
        cur += c;
        ans = max(ans, cur);
        q.push(cur);
    }
    cout<<ans<<endl;
    return 0;
}