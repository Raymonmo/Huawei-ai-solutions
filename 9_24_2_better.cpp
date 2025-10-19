#include <bits/stdc++.h>
#include <iomanip>
#include <unordered_map>
using namespace std;

double distance(vector<double>& vec1, vector<double>& vec2){
    double ans = 0.0;
    for(int i = 0; i < vec1.size(); i++){
        ans += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    }
    return sqrt(ans);
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<vector<double>> ordinate(n,vector<double> (2));
    for(int i = 0; i < n; i++){
        cin>>ordinate[i][0]>>ordinate[i][1];
    }

    vector<vector<double>> center(k, vector<double> (2));
    for(int i = 0; i < k; i++){
        center[i][0] = ordinate[i][0];
        center[i][1] = ordinate[i][1];
    }

    int iterations = 100;
    double eps = 1e-6;

    for(int iteration = 0; iteration < iterations; iteration++){
        vector<vector<double>> new_center(k, vector<double> (2,0.0));
        vector<double> num(k,0);
        for(int i = 0; i < n; i++){
            double dis = distance(ordinate[i], center[0]);
            int tar = 0;
            for(int j = 1; j < k; j++){
                if(distance(ordinate[i], center[j]) < dis){
                    dis = distance(ordinate[i], center[j]);
                    tar = j;
                }
            }
            new_center[tar][0] += ordinate[i][0];
            new_center[tar][1] += ordinate[i][1];
            num[tar]++;
        }
        double move = 0.0;
        for(int i = 0; i < k; i++){
            new_center[i][0] /= num[i];
            new_center[i][1] /= num[i];
            move += distance(new_center[i], center[i]);
        }
        if(move <= eps) break;

        center = new_center;
    }
    vector<vector<int>> groups(k);
    unordered_map<int, int> query;
    for(int i = 0; i < n; i++){
        double min_dis = distance(ordinate[i], center[0]);
        int tar = 0;
        for(int j = 1; j < k; j++){
            if(min_dis > distance(ordinate[i], center[j])){
                min_dis = distance(ordinate[i], center[j]);
                tar = j;
            }
        }
        groups[tar].push_back(i);
        query[i] = tar;
    }

    vector<double> ss(k,0);
    for(int i = 0; i < n; i++){
        double a = 0.0;
        int group1 = query[i];
        for(int j : groups[group1]){
            a += distance(ordinate[i], ordinate[j]);
        }
        a = groups[group1].size() == 1 ? 0 : a / (groups[group1].size() - 1.0);

        double min_b = 10000000000;
        for(int j = 0; j < k; j++){
            if(j == group1) continue;
            double now_b = 0.0;
            for(int c : groups[j]){
                now_b += distance(ordinate[i], ordinate[c]);
            }
            now_b = groups[j].size() > 0 ? now_b / groups[j].size() : 0;
            min_b = min(min_b, now_b);
        }

        double s = (min_b - a) / max(min_b, a);
        ss[group1] += s;
    }
    double min_s = 100000000;
    int tar = 0;
    for(int i = 0; i < k; i++){
        ss[i] = groups[i].size() > 0 ? ss[i] / groups[i].size() : 0;
        if(ss[i] < min_s){
            min_s = ss[i];
            tar = i;
        }
    }

    cout<<fixed<<setprecision(2)<<center[tar][0]<<","<<center[tar][1];

    return 0;
}