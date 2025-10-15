#include <bits/stdc++.h>
#include <queue>
using namespace std;
int main(){
    int n,m,p,k;
    cin>>n>>m>>p>>k;
    int num = n / m;
    if(n % m != 0 || p > m || k > p * num) {
        cout<<"error"<<endl;
        return 0;
    }

    vector<double> por1(n);
    vector<double> max_p(m);
    for(int i = 0; i < n; i++){
        cin>>por1[i];
    }
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> q;
    for(int i = 0; i < m; i++){
        double maxp = por1[i * num];
        for(int j = 1; j < num; j++){
            maxp = max(maxp, por1[i * num + j]);
        }
        max_p[i] = maxp;
        q.push({maxp, i});
        if(q.size() > p){
            q.pop();
        }
    }

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q2;
    while(!q.empty()){
        int idx = q.top().second;
        q.pop();
        for(int j = 0; j < num; j++){
            int idx2 = idx * num + j;
            q2.push({por1[idx2], idx2});
            if(q2.size() > k){
                q2.pop();
            }
        }
    }
    priority_queue<int, vector<int>, greater<int>> ans;
    while(!q2.empty()){
        ans.push(q2.top().second);
        q2.pop();
    }
    bool skip = 1;
    while(!ans.empty()){
        if(skip){
            skip = 0;
        } else {
            cout<<' ';
        }
        cout<<ans.top();
        ans.pop();
    }
    return 0;
//     vector<double> por2(m);
//     vector<int> target(m);
//     for(int i = 0; i < m; i++){
//         double maxP = por1[i * num];
//         int tar = i * num;
//         for(int j = 0; j < num; j++){
//             if(maxP < por1[i*num + j]){
//                 maxP = por1[i*num + j];
//                 tar = i * num + j;
//             }
//         }
//         por2[i] = maxP;
//         target[i] = tar;
//     }

//     priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> q;
//     for(int i = 0; i < m; i++){
//         q.push({por2[i],i});
//         if(q.size() > p){
//             q.pop();
//         }
//     }
//     //cout<<q.size()<<endl;
// priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> ans;
//     while(q.size() > 0){
//         int now = q.top().second;
//         for(int i = 0; i < num; i++){
//             ans.push({por1[i + now * num],i + now * num});
//         }
//         q.pop();
//     }
//     while(ans.size() > k){
//         ans.pop();
//     }
//     priority_queue<int, vector<int>, greater<int>> ans2;
//     while(!ans.empty()){
//         ans2.push(ans.top().second);
//         ans.pop();
//     }
//     while(ans2.size() > 1){
//         cout<<ans2.top()<<" ";
//         ans2.pop();
//     }
//     cout<<ans2.top();
    
//     return 0;
}