#include <bits/stdc++.h>
using namespace std;

double round3(double x) {
    return round(x * 1000.0) / 1000.0;
}
int main(){
    string line;
    getline(cin,line);
    bool first = true;
    bool second = false;
    vector<int> num;
    vector<int> window;
    int tmp = 0;
    int maxWindow = 0;
    int minWindow = INT_MAX;
    for(auto c : line){
        if(first){
            if(c >= '0' && c <= '9'){
                tmp = tmp * 10 + (c - '0');
            } else if(c == ','){
                num.push_back(tmp);
                tmp = 0;
            } else if(c == ']'){
                num.push_back(tmp);
                first = false;
                tmp = 0;
            }
        } else {
            if(c >= '0' && c <= '9'){
                tmp = tmp * 10 + (c - '0');
            } else if(c == ','){
                if(second){
                    window.push_back(tmp);
                    maxWindow = max(maxWindow,tmp);
                    minWindow = min(minWindow,tmp);
                    tmp = 0;
                } else {
                    second = true;
                }
            } else if(c == ']'){
                window.push_back(tmp);
                maxWindow = max(maxWindow,tmp);
                minWindow = min(minWindow,tmp);
            }
        }
    }
    if(num.size() < minWindow || window.size() == 0) {
        cout<<"[]";
        return 0;
    }
    int n = num.size() - maxWindow + 1;
    if(n <= 0){
        cout<<"[]";
        return 0;
    }
    int m = window.size() * 5;
    vector<vector<double>> ans(n, vector<double> (m));

    for(int now = 0; now < window.size(); now++){
        int w = window[now];
        int start = maxWindow - w;
        int tar = 0;
        while(start + w - 1 < num.size()){
            int maxnum = num[start], minnum = num[start];
            double meany = 0.0, sigma = 0.0, k = 0.0, meanx = 0.0, x2 = 0.0;
            double multiple = 0;
            for(int i = start; i < start + w; i++){
                meanx += i;
                meany += num[i];
                maxnum = max(maxnum,num[i]);
                minnum = min(minnum,num[i]);
                multiple += i * num[i];
                x2 += i*i;
            }
            k = (w * multiple - meanx * meany) / (w * x2 - meanx * meanx);
            meanx /= w;
            meany /= w;
            for(int i = start; i < start + w; i++){
                sigma += (num[i] - meany) * (num[i] - meany);
            }
            sigma = sqrt(sigma/(w - 1));
            meany = round3(meany);
            sigma = round3(sigma);
            k = round3(k);
            ans[tar][5 * now] = meany;
            ans[tar][1 + 5 * now] = sigma;
            ans[tar][2 + 5 * now] = minnum;
            ans[tar][3 + 5 * now] = maxnum;
            if(w == 1){
                ans[tar][4 + 5 * now] = 0;
            } else {
                ans[tar][4 + 5 * now] = k;
            }
            start++;
            tar++;
        }
    }

    for(int i = 0; i < n; i++){
        cout<<"[";
        for(int j = 0; j < ans[0].size(); j++){
            if(j == 0){
                cout<<ans[i][j];
            } else {
                cout<<", "<<ans[i][j];
            }
        }
        cout<<"]"<<endl;
    }

    return 0;
}