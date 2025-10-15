#include <bits/stdc++.h>
#include <sstream>
using namespace std;

double round3(double x){
    return round(1000 * x) / 1000;
}

void calculate(vector<int>& vec){
    int m = vec.size();
    double mean = 0.0;
    int min_num = INT_MAX;
    int max_num = INT_MIN;

    double x = 0, x2 = 0;
    double xy = 0;

    for(int i = 0; i < m; i++){
        mean += double(vec[i]);
        min_num = min(min_num, vec[i]);
        max_num = max(max_num, vec[i]);
        x += i;
        x2 += i * i;
        xy += i * vec[i];
    }
    double k = double(m * xy - x * mean) / (m * x2 - x * x);

    mean = mean / double(m);

    double s = 0.0;
    for(int c : vec){
        s += double(c - mean) * (c - mean);
    }
    s = m - 1 == 0 ? 0 : sqrt(s / double(m - 1));
    cout<<round3(mean)<<", "<<round3(s)<<", "<<min_num<<", "<<max_num<<", "<<round3(k);
}

int main(){
    string line;
    getline(cin,line);
    
    vector<int> input_array;
    int now = 1;
    int num = 0;
    while(line[now] != ']'){
        if(line[now] >= '0' && line[now] <= '9'){
            int tar = line[now] - '0';
            num = num * 10 + tar;
        } else if(line[now] == ',') {
            input_array.push_back(num);
            num = 0;
        }
        now++;
    }
    input_array.push_back(num);
    num = 0;

    while(line[now] != '[') now++;
    now++;

    int max_window = INT_MIN;
    int min_window = INT_MAX;
    vector<int> windows;
    while(line[now] != ']'){
        if(line[now] >= '0' && line[now] <= '9'){
            int tar = line[now] - '0';
            num = num * 10 + tar;
        } else if(line[now] == ',') {
            windows.push_back(num);
            max_window = max(max_window, num);
            min_window = min(min_window, num);
            num = 0;
        }
        now++;
    }
    windows.push_back(num);
    max_window = max(max_window, num);
    min_window = min(min_window, num);
    num = 0;

    int n = input_array.size() - max_window + 1;

    if(max_window > input_array.size() || windows.size() == 0){
        cout<<"[]";
        return 0;
    }

    for(int j = 0; j + max_window <= input_array.size(); j++){
        cout<<'[';
        bool first = true;
        for(int w : windows){
            int start = max_window - w + j;
            vector<int> vec;
            for(int i = start; i < start + w ; i++){
                vec.push_back(input_array[i]);
            }
            if(first) first = false;
            else {
                cout<<", ";
            }
            calculate(vec);
        }
        cout<<']'<<endl;
    }


    return 0;
}