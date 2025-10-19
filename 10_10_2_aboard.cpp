#include <bits/stdc++.h>
using namespace std;

void calculation(vector<double>& c){
    double n = c.size();
    double mean = 0.0;
    double maxnum = c[0];
    double minnum = c[0];
    double ptp = 0.0;
    double std = 0.0;
    double var = 0.0;
    double skew = 0.0;
    double kurt = 0.0;

    for(auto x : c){
        mean += x;
        maxnum = max(maxnum, x);
        minnum = min(minnum, x);
    }
    ptp = maxnum - minnum;
    mean = mean / n;

    for(auto x : c){
        var += (x - mean) * (x - mean);
        skew += (x - mean) * (x - mean) * (x - mean);
        kurt += (x - mean) * (x - mean) * (x - mean) * (x - mean);
    }
    var = var / n;
    std = var == 0 ? 0 : sqrt(var);
    skew = std == 0 ? 0 : (skew / n) / (std * var);
    kurt = std == 0 ? 0 : (kurt / n) / (var * var) - 3;
    cout<<fixed<<setprecision(2)<<mean<<" "<<maxnum<<" "<<minnum<<" "<<ptp<<" "<<std<<" "<<var<<" "<<skew<<" "<<kurt;
    return;
}

int main(){
    double input;
    vector<vector<double>> data;
    vector<double> tmp;
    while(cin>>input){
        if(input >= 1e9 && !tmp.empty()){
            while(tmp.size() < 19){
                tmp.insert(tmp.begin() + 11, 0.0);
            }
            data.push_back(tmp);
            tmp = {};
        }
        tmp.push_back(input);
    }
    if(!tmp.empty()){
        while(tmp.size() < 19){
            tmp.insert(tmp.begin() + 11, 0.0);
        }
    }
    data.push_back(tmp);

    int n = data.size();
    vector<vector<double>> deal(19, vector<double> (n));
    for(int i = 0; i < 19; i++){
        for(int j = 0; j < n; j++){
            deal[i][j] = data[j][i];
        }
    }

    for(int i = 0; i < 19; i++){
        if(i) cout<<" ";
        calculation(deal[i]);
    }
    return 0;
}