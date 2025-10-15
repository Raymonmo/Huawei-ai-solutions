#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

double round2(double x){
    return round(100 * x) / 100;
}

const double threshold = 1e-6;
double distance(double x1, double y1, double x2, double y2){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main(){
    int n,k;
    cin>>n>>k;
    vector<vector<double>> points(n, vector<double> (2));
    for(int i = 0; i < n; i++){
        cin>>points[i][0]>>points[i][1];
    }

    if(k >= n){
        cout<<round2(points[0][0])<<" "<<round2(points[0][1])<<endl;
        return 0;
    }

    vector<vector<double>> center(k, vector<double> (2));
    for(int i = 0; i < k; i++){
        center[i][0] = points[i][0];
        center[i][1] = points[i][1];
    }
    int iteration = 0;
    while(iteration < 100){
        iteration++;
        vector<vector<double>> now_center(k, vector<double> (2));
        vector<vector<double>> xysum(k, vector<double> (3,0));
        for(int i = 0; i < n; i++){
            int tar = 0;
            double min_dis = 0;
            bool choose3 = 1;
            for(int j = 0; j < k; j++){
                double now_dis = distance(points[i][0], points[i][1], center[j][0], center[j][1]);
                if(choose3){
                    min_dis = now_dis;
                    tar = j;
                    choose3 = 0;
                } else {
                    if(now_dis < min_dis){
                        min_dis = now_dis;
                        tar = j;
                    }
                }
            }
            xysum[tar][0] += double(points[i][0]);
            xysum[tar][1] += double(points[i][1]);
            xysum[tar][2]++;
        }
        double moved = 0;
        for(int i = 0; i < k; i++){
            if(xysum[i][2] == 0) continue;
            now_center[i][0] = xysum[i][0] / xysum[i][2];
            now_center[i][1] = xysum[i][1] / xysum[i][2];
            moved += fabs(now_center[i][0] - center[i][0]) + fabs(now_center[i][1] - center[i][1]);
        }
        center = now_center;
        if(moved <= threshold) break;
    }
    // for(int i = 0; i < k; i++){
    //     cout<<round2(center[i][0])<<" "<<round2(center[i][1])<<endl;
    // }
    if(k == 1){
        cout<<round2(center[0][0])<<" "<<round2(center[0][1])<<endl;
        return 0;
    }

    vector<vector<int>> group(k);

    for(int i = 0; i < n; i++){
        int tar = -1;
        double min_dis = INT_MAX;
        for(int j = 0; j < k; j++){
            double now_dis = distance(points[i][0], points[i][1], center[j][0], center[j][1]);
            if(now_dis < min_dis){
                min_dis = now_dis;
                tar = j;
            }
        }
        group[tar].push_back(i);
    }
    double min_s = 0;
    bool choose2 = 1;
    int ans_index = 0;
    for(int j = 0; j < k; j++){
        int len = group[j].size();
        double s = 0;
        if(len > 1){
        for(int i = 0; i < len; i++){
            
            double dis1 = 0;
            int now_index = group[j][i];
            for(int a = 0; a < len; a++){
                if(a == i) continue;
                int tar_index = group[j][a];
                dis1 += sqrt(distance(points[now_index][0], points[now_index][1], 
                points[tar_index][0], points[tar_index][1]));
            }
            dis1 /= len - 1;
            double min_bi = 0;
            bool choose = 1;
            for(int b = 0; b < k; b++){
                if(b == j) continue;
                double now_bi = 0;
                int len2 = group[b].size();
                if(len2 == 0) continue;
                for(int x : group[b]){
                    now_bi += sqrt(distance(points[now_index][0], points[now_index][1], 
                    points[x][0], points[x][1]));
                }
                now_bi /= len2;
                if(choose) {
                    min_bi = now_bi;
                    choose = 0;
                } else {
                    min_bi = min(min_bi, now_bi);
                }
                
            }
            double now_s = (max(min_bi, dis1) == 0) ? 0 : (min_bi - dis1) / max(min_bi, dis1);
            s += now_s;
        }
        s = s / len;
        } else {
            s = 0;
        }

        //cout<<j<<" "<<s<<endl;
        if(choose2){
            min_s = s;
            ans_index = j;
            choose2 = 0;
        } else {
            if(min_s > s){
                min_s = s;
                ans_index = j;
            }
        }
    }
    cout<<fixed<<setprecision(2)<<round2(center[ans_index][0])<<","<<round2(center[ans_index][1])<<endl;
    return 0;
}