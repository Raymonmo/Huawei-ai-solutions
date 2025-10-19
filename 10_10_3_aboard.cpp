#include <bits/stdc++.h>
using namespace std;

vector<double> w(7, 0.0);
double bias = 0.0;

vector<double> encode(string& s){
    vector<double> res(7,0);
    for(char c : s){
        res[c - 'A'] = 1.0;
    }
    return res;
}

void train(vector<vector<double>>& encode, vector<int>& intent){
    int iterations = 20;
    double lr = 0.1;
    for(int iteration = 0; iteration < iterations; iteration++){
        for(int i = 0; i < encode.size(); i++){
            vector<double> now = encode[i];
            double y = bias;
            for(int j = 0; j < 7; j++){
                y += w[j] * now[j];
            }
            double p = 1.0/(1 + exp(-y));
            double dz = p - intent[i];
            for(int j = 0; j < 7; j++){
                w[j] -= lr * dz * now[j];
            }
            bias -= lr * dz;
        }
    }
}

int predict(string& s){
    vector<double> res(7,0);
    for(char c : s){
        res[c - 'A'] = 1;
    }
    double y = bias;
    for(int j = 0; j < 7; j++){
        y += res[j] * w[j];
    }
    double z = 1.0 / (1 + exp(-y));
    if(z <= 0.5) return 0;
    else return 1;
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<string> str(N);
    vector<int> intent(N);
    vector<vector<double>> encodes(N, vector<double> (7));
    for(int i = 0; i < N; i++){
        cin>>str[i]>>intent[i];
        encodes[i] = encode(str[i]);
    }

    train(encodes, intent);

    for(int i = 0; i < M; i++){
        string now;
        cin>>now;
        cout<<predict(now)<<endl;
    }
    return 0;
}