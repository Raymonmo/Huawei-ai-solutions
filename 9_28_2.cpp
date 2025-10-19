#include <bits/stdc++.h>
#include <queue>
using namespace std;

double d_cal(vector<int> &a, vector<int> &b){
    int intersection = min(a[0], b[0]) * min(a[1], b[1]);
    int u = a[0] * a[1] + b[0] * b[1] - intersection;
    return 1.0 - double(intersection) / (double(u) + 1e-16);
}

int main(){
    int N,K,T;
    cin>>N>>K>>T;

    vector<vector<int>> anchor(N, vector<int> (2));
    vector<vector<int>> center(K, vector<int> (2));

    for(int i = 0; i < N; i++){
        cin>>anchor[i][0]>>anchor[i][1];
        if(i < K){
            center[i][0] = anchor[i][0];
            center[i][1] = anchor[i][1];
        }
    }

    double eps = 1e-4;
    for(int iteration = 0; iteration < T; iteration++){
        vector<vector<int>> sum(K, vector<int> (2, 0));
        vector<int> count(K, 0);
        for(int i = 0; i < N; i++){
            double min_d = 2.0;
            int tar = 0;
            for(int j = 0; j < K; j++){
                double now_d = d_cal(anchor[i], center[j]);
                if(now_d < min_d){
                    min_d = now_d;
                    tar = j;
                }
            }
            sum[tar][0] += anchor[i][0];
            sum[tar][1] += anchor[i][1];
            count[tar]++;
        }
        double sum_d = 0.0;
        for(int j = 0; j < K; j++){
            sum[j][0] /= count[j];
            sum[j][1] /= count[j];
            sum_d += d_cal(center[j], sum[j]);
        }
        center = sum;
        if(sum_d < eps){
            break;
        }
    }
    priority_queue<pair<int,int>> area;
    for(int i = 0; i < K; i++){
        area.push({center[i][0] * center[i][1], i});
    }
    for(int i = 0; i < K; i++){
        int tar = area.top().second;
        area.pop();
        cout<<center[tar][0]<<" "<<center[tar][1]<<endl;
    }
    return 0;
}