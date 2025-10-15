#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

double distance(vector<double> x, vector<double> y){
    int size = x.size();
    double sum = 0;
    for(int i = 0; i < size; i++){
        sum += (x[i] - y[i]) * (x[i] - y[i]);
    }
    return sqrt(sum);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k,m,n,s;
    cin>>k>>m>>n>>s;

    vector<double> target(n);
    //待分类样本
    for(int i = 0; i < n; i++){
        double tar;
        cin>>tar;
        target[i] = tar; 
    }
    //优先队列用来存储距离最小的K个点
    priority_queue <pair<double,double>> q;

    for(int i = 0; i < m; i++){
        vector<double> x(n);
        for(int j = 0; j < n; j++){
            double tmp;
            cin>>tmp;
            x[j] = tmp;
        }
        double label;
        cin>>label;
        double dis = distance(x,target);
        q.push({dis,label});
        if(q.size() > k){
            q.pop();
        }
    }

    vector<int> count(s);
    int maxnum = 0;
    int ans = 0;
    while(!q.empty()){
        auto x = q.top();
        q.pop();
        int sign = int(x.second);
        count[sign]++;
        if(count[sign] >= maxnum){
            maxnum = count[sign];
            ans = sign;
        }
    }
    cout<<ans<<" "<<maxnum<<endl;
    return 0;
}