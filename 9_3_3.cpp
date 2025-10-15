#include <bits/stdc++.h>
#include <queue>
#include <string>
using namespace std;

double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

void fill(vector<double>& vec, int tar){
    int n = vec.size();
    priority_queue<double> q;
    double sum = 0.0;
    int count = 0;
    for(double c : vec){
        if( (tar < 2 && c < 0) ||
            (tar < 4 && (c < 0 || c > 1000)) ||
            (tar == 4 && (c < 0 || c > 20))) continue;
        else {
            sum += c;
            count++;
            q.push(c);
        }
    }
    double mean = sum / count;
    double mid = 0.0;
    if(count % 2 == 1){
        while(q.size() > count / 2 + 1){
            q.pop();
        }
        mid = q.top();
    } else {
        while(q.size() > count / 2 + 1){
            q.pop();
        }
        mid += q.top();
        q.pop();
        mid += q.top();
        mid = mid / 2;
    }
    // cout<<tar<<endl;
    // cout<<mean<<endl;
    // cout<<mid<<endl;
    for(int i = 0; i < n; i++){
        if(vec[i] == -1) vec[i] = mean;
        else if(vec[i] == -2) vec[i] = mid;
    }
    return;
}

void process(vector<vector<double>>& data){
    int n = data.size();
    for(int i = 0; i < 6; i++){
        vector<double> vec(n);
        for(int j = 0; j < n; j++){
            vec[j] = data[j][i];
        }
        fill(vec, i);
        for(int j = 0; j < n; j++){
            data[j][i] = vec[j];
        }
    }
    return;
}

int main(){
    int N;
    cin>>N;
    cin.ignore();
    vector<vector<double>> data(N, vector<double> (6));
    for(int i = 0; i < N; i++){
        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        int count = 0;
        getline(ss, token, ',');
        while(getline(ss, token, ',')){
            if(token == "NaN"){
                data[i][count] = -1.0;
            } else {
                double now = stod(token);
                if(count < 2 && now < 0){
                    data[i][count] = -2.0;
                } else if (count < 4 && (now < 0 || now > 1000)){
                    data[i][count] = -2.0;
                } else if (count == 4 && (now < 0 || now > 20)){
                    data[i][count] = -2.0;
                } else {
                    data[i][count] = now;
                }
            }
            count++;
        }
    }

    process(data);

    double lr = 0.01;
    vector<double> w(5, 0.0);
    double b = 0.0;

    int iterations = 100;
    for(int iteration = 0; iteration < iterations; iteration++){
        vector<double> grad_w(5, 0.0);
        double grad_b = 0.0;
        for(int i = 0; i < N; i++){
            double dj = b;
            for(int j = 0; j < 5; j++){
                dj += w[j] * data[i][j];
            }
            double prediction = sigmoid(dj);
            double error = prediction - data[i][5];
            for(int j = 0; j < 5; j++){
                grad_w[j] += error * data[i][j];
            }
            grad_b += error;
        }
        for(int j = 0; j < 5; j++){
            grad_w[j] /= N;
        }
        grad_b /= N;

        for(int j = 0; j < 5; j++){
            w[j] -= lr * grad_w[j];
        }
        b -= lr * grad_b;
    }

    int M;
    cin>>M;
    cin.ignore();
    vector<vector<double>> data_predict(M, vector<double> (6));
    for(int i = 0; i < M; i++){
        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        int count = 0;
        getline(ss, token, ',');
        while(getline(ss, token, ',')){
            if(token == "NaN"){
                data_predict[i][count] = -1.0;
            } else {
                double now = stod(token);
                if(count < 2 && now < 0){
                    data_predict[i][count] = -2.0;
                } else if (count < 4 && (now < 0 || now > 1000)){
                    data_predict[i][count] = -2.0;
                } else if (count == 4 && (now < 0 || now > 20)){
                    data_predict[i][count] = -2.0;
                } else {
                    data_predict[i][count] = now;
                }
            }
            count++;
        }
    }

    process(data_predict);

    for(int i = 0; i < M; i++){
        double res = b;
        for(int j = 0; j < 5; j++){
            res += w[j] * data_predict[i][j];
        }
        double ans = sigmoid(res) < 0.5 ? 0 : 1;
        cout<<ans<<endl;
    }

    return 0;
}