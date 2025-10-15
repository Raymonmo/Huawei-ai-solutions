#include <bits/stdc++.h>
#include <sstream>
using namespace std;

vector<vector<double>> getParam(int L, int D){
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<vector<double>> param(L, vector<double> (D));
    for(int i = 0; i < L; i++){
        for(int j = 0; j < D; j++){
            string token;
            getline(ss, token, ',');
            param[i][j] = stod(token);
        }
    }
    return param;
}

vector<vector<double>> multi(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2, double x){
    int m = matrix1.size();
    int n = matrix2[0].size();
    int b = matrix1[0].size();
    vector<vector<double>> res(m, vector<double> (n,0));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < b; k++){
                res[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            res[i][j] = res[i][j] / x;
        }
    }
    return res;
}

vector<vector<double>> trans(const vector<vector<double>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<double>> res(n, vector<double> (m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            res[i][j] = matrix[j][i];
        }
    }
    return res;
}

vector<vector<double>> softmax(const vector<vector<double>>& matrix){
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<double>> ans = matrix;
    for(int i = 0; i < m; i++){
        double max_num = ans[i][0];
        for(int j = 1; j < n; j++){
            max_num = max(max_num, ans[i][j]);
        }
        double sum = 0.0;
        for(int j = 0; j < n; j++){
            ans[i][j] = exp(ans[i][j] - max_num);
            sum += ans[i][j];
        }
        for(int j = 0; j < n; j++){
            ans[i][j] = ans[i][j] / sum;
        }
    }
    return ans;
}

vector<vector<double>> add(const vector<vector<double>>& matrix1, const vector<vector<double>>& matrix2){
    vector<vector<double>> res = matrix1;
    for(int i = 0; i < matrix1.size(); i++){
        for(int j = 0; j < matrix1[0].size(); j++){
            res[i][j] += matrix2[0][j];
        }
    }
    return res;
}

int main(){
    int L, D;
    string line1;
    getline(cin,line1);
    stringstream ss1(line1);
    string token;
    getline(ss1, token, ',');
    L = stoi(token);
    getline(ss1, token, ',');
    D = stoi(token);

    vector<vector<double>> input = getParam(L, D);

    vector<vector<double>> Wq1 = getParam(D, D); 
    vector<vector<double>> Wk1 = getParam(D, D);
    vector<vector<double>> Wv1 = getParam(D, D);
    vector<vector<double>> Wfc1 = getParam(D, D);
    vector<vector<double>> bfc1 = getParam(1, D);

    vector<vector<double>> Q1 = multi(input, Wq1, 1);
    vector<vector<double>> K1 = multi(input, Wk1, 1);
    vector<vector<double>> V1 = multi(input, Wv1, 1);

    vector<vector<double>> inside1 = multi(Q1, trans(K1), sqrt(D));
    vector<vector<double>> output1 = multi(softmax(inside1), V1, 1);

    vector<vector<double>> input2 = add(multi(output1, Wfc1, 1), bfc1);

    vector<vector<double>> Wq2 = getParam(D, D); 
    vector<vector<double>> Wk2 = getParam(D, D);
    vector<vector<double>> Wv2 = getParam(D, D);
    vector<vector<double>> Wfc2 = getParam(D, D);
    vector<vector<double>> bfc2 = getParam(1, D);

    vector<vector<double>> Q2 = multi(input2, Wq2, 1);
    vector<vector<double>> K2 = multi(input2, Wk2, 1);
    vector<vector<double>> V2 = multi(input2, Wv2, 1);

    vector<vector<double>> inside2 = multi(Q2, trans(K2), sqrt(D));
    vector<vector<double>> output2 = multi(softmax(inside2), V2, 1);

    vector<vector<double>> ans = add(multi(output2, Wfc2, 1), bfc2);

    bool first = true;
    for(int i = 0; i < L; i++){
        for(int j = 0; j < D; j++){
            if(!first) cout<<',';
            else first = false;
            cout<<fixed<<setprecision(2)<<ans[i][j];
        }
    }
    return 0;
}