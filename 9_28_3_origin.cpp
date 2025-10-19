#include <bits/stdc++.h>
using namespace std;

static void print3D(const vector<vector<vector<double>>> &A) {
    cout << "[";
    for (int b = 0; b < (int)A.size(); ++b) {
        if (b) cout << ", ";
        cout << "[";
        for (int i = 0; i < (int)A[b].size(); ++i) {
            if (i) cout << ", ";
            cout << "[";
            for (int j = 0; j < (int)A[b][i].size(); ++j) {
                if (j) cout << ", ";
                double v = A[b][i][j];
                if (fabs(v) < 0.005) v = 0.0; // 避免-0.00
                cout.setf(std::ios::fixed); cout<<setprecision(2)<<v;
            }
            cout << "]";
        }
        cout << "]";
    }
    cout << "]\n";
}

int main(){
    string line;
    getline(cin, line);
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while(getline(ss, token, ';')){
        tokens.push_back(token);
    }
    int num_heads = stoi(tokens[0]);

    vector<vector<vector<double>>> X;
    int now = 0;
    bool start1 = false, start2 = false, start3 = false;
    double num = 0.0;
    int negative = 1;
    bool small = false;
    int right = 0;
    vector<double> tmp1;
    vector<vector<double>> tmp2;
    while(now < tokens[1].length()){
        string s = tokens[1];
        if(s[now] == '['){
            if(!start1){
                start1 = true;
            } else {
                if(!start2){
                    start2 = true;
                } else {
                    if(!start3){
                        start3 = true;
                    }
                }
            }
        } else if(s[now] == '-'){
            negative = -1;
        } else if(s[now] == '.'){
            small = true;
        } else if(s[now] >= '0' && s[now] <= '9'){
            if(small){
                right++;
                num += (s[now] - '0') * pow(0.1, right);
            } else {
                num = num * 10 + (s[now] - '0');
            }
        } else if(s[now] == ','){
            if(num != 0){
                tmp1.push_back(num * negative);
                num = 0;
                negative = 1;
                small = false;
                right = 0;
            }
        } else if(s[now] == ']'){
            if(start3){
                start3 = false;
                tmp1.push_back(num * negative);
                num = 0;
                negative = 1;
                small = false;
                right = 0;

                tmp2.push_back(tmp1);
                tmp1 = {}; //tmp1.clear();
            } else {
                if(start2){
                    start2 = false;
                    X.push_back(tmp2);
                    tmp2 = {};
                } else {
                    start1 = false;
                }
            }
        }
        now++;
    }
    // for(auto c : X){
    //     for(auto v : c){
    //         for(auto b : v) cout<<b<<endl;
    //     }
    // }

    vector<vector<double>> Q, K, V, W;
    now = 0;
    start2 = false;
    start3 = false;
    num = 0.0;
    negative = 1;
    small = false;
    right = 0;
    tmp1 = {};
    while(now < tokens[2].length()){
        string s = tokens[2];
        if(s[now] == '['){
            if(!start2){
                start2 = true;
            } else {
                if(!start3){
                    start3 = true;
                }
            }
        } else if(s[now] == '-'){
            negative = -1;
        } else if(s[now] == '.'){
            small = true;
        } else if(s[now] >= '0' && s[now] <= '9'){
            if(small){
                right++;
                num += (s[now] - '0') * pow(0.1, right);
            } else {
                num = num * 10 + (s[now] - '0');
            }
        } else if(s[now] == ','){
            if(num != 0){
                tmp1.push_back(num * negative);
                //for(auto c : tmp1) cout<<c<<endl;
                num = 0;
                negative = 1;
                small = false;
                right = 0;
            }
        } else if(s[now] == ']'){
            if(start3){
                start3 = false;
                tmp1.push_back(num * negative);
                num = 0;
                negative = 1;
                small = false;
                right = 0;

                Q.push_back(tmp1);
                tmp1 = {}; //tmp1.clear();
            } else {
                if(start2){
                    start2 = false;
                }
            }
        }
        now++;
    }

    now = 0;
    start2 = false;
    start3 = false;
    num = 0.0;
    negative = 1;
    small = false;
    right = 0;
    tmp1 = {};
    while(now < tokens[3].length()){
        string s = tokens[3];
        if(s[now] == '['){
            if(!start2){
                start2 = true;
            } else {
                if(!start3){
                    start3 = true;
                }
            }
        } else if(s[now] == '-'){
            negative = -1;
        } else if(s[now] == '.'){
            small = true;
        } else if(s[now] >= '0' && s[now] <= '9'){
            if(small){
                right++;
                num += (s[now] - '0') * pow(0.1, right);
            } else {
                num = num * 10 + (s[now] - '0');
            }
        } else if(s[now] == ','){
            if(num != 0){
                tmp1.push_back(num * negative);
                //for(auto c : tmp1) cout<<c<<endl;
                num = 0;
                negative = 1;
                small = false;
                right = 0;
            }
        } else if(s[now] == ']'){
            if(start3){
                start3 = false;
                tmp1.push_back(num * negative);
                num = 0;
                negative = 1;
                small = false;
                right = 0;

                K.push_back(tmp1);
                tmp1 = {}; //tmp1.clear();
            } else {
                if(start2){
                    start2 = false;
                }
            }
        }
        now++;
    }

    // for(auto c : K){
    //     for(auto v : c){
    //         cout<<v<<endl;
    //     }
    // }

    now = 0;
    start2 = false;
    start3 = false;
    num = 0.0;
    negative = 1;
    small = false;
    right = 0;
    tmp1 = {};
    while(now < tokens[4].length()){
        string s = tokens[4];
        if(s[now] == '['){
            if(!start2){
                start2 = true;
            } else {
                if(!start3){
                    start3 = true;
                }
            }
        } else if(s[now] == '-'){
            negative = -1;
        } else if(s[now] == '.'){
            small = true;
        } else if(s[now] >= '0' && s[now] <= '9'){
            if(small){
                right++;
                num += (s[now] - '0') * pow(0.1, right);
            } else {
                num = num * 10 + (s[now] - '0');
            }
        } else if(s[now] == ','){
            if(num != 0){
                tmp1.push_back(num * negative);
                //for(auto c : tmp1) cout<<c<<endl;
                num = 0;
                negative = 1;
                small = false;
                right = 0;
            }
        } else if(s[now] == ']'){
            if(start3){
                start3 = false;
                tmp1.push_back(num * negative);
                num = 0;
                negative = 1;
                small = false;
                right = 0;

                V.push_back(tmp1);
                tmp1 = {}; //tmp1.clear();
            } else {
                if(start2){
                    start2 = false;
                }
            }
        }
        now++;
    }

    // for(auto c : V){
    //     for(auto v : c){
    //         cout<<v<<endl;
    //     }
    // }

    now = 0;
    start2 = false;
    start3 = false;
    num = 0.0;
    negative = 1;
    small = false;
    right = 0;
    tmp1 = {};
    while(now < tokens[5].length()){
        string s = tokens[5];
        if(s[now] == '['){
            if(!start2){
                start2 = true;
            } else {
                if(!start3){
                    start3 = true;
                }
            }
        } else if(s[now] == '-'){
            negative = -1;
        } else if(s[now] == '.'){
            small = true;
        } else if(s[now] >= '0' && s[now] <= '9'){
            if(small){
                right++;
                num += (s[now] - '0') * pow(0.1, right);
            } else {
                num = num * 10 + (s[now] - '0');
            }
        } else if(s[now] == ','){
            if(num != 0){
                tmp1.push_back(num * negative);
                //for(auto c : tmp1) cout<<c<<endl;
                num = 0;
                negative = 1;
                small = false;
                right = 0;
            }
        } else if(s[now] == ']'){
            if(start3){
                start3 = false;
                tmp1.push_back(num * negative);
                num = 0;
                negative = 1;
                small = false;
                right = 0;

                W.push_back(tmp1);
                tmp1 = {}; //tmp1.clear();
            } else {
                if(start2){
                    start2 = false;
                }
            }
        }
        now++;
    }

    // for(auto c : W){
    //     for(auto v : c){
    //         cout<<v<<endl;
    //     }
    // }


    int batch_size = X.size();
    int n = X[0].size();
    int d_model = Q.size();
    int d_k = d_model / num_heads;

    vector<vector<vector<double>>> Q_dealed(batch_size, vector<vector<double>>(n, vector<double> (d_model, 0.0)));
    vector<vector<vector<double>>> K_dealed(batch_size, vector<vector<double>>(n, vector<double> (d_model, 0.0)));
    vector<vector<vector<double>>> V_dealed(batch_size, vector<vector<double>>(n, vector<double> (d_model, 0.0))); 

    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < d_model; k++){
                double sum = 0.0;
                for(int a = 0; a < d_model; a++){
                    sum += X[i][j][a] * Q[a][k];
                }
                Q_dealed[i][j][k] = sum;
            }
        }
    }
    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < d_model; k++){
                double sum = 0.0;
                for(int a = 0; a < d_model; a++){
                    sum += X[i][j][a] * K[a][k];
                }
                K_dealed[i][j][k] = sum;
            }
        }
    }
    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < d_model; k++){
                double sum = 0.0;
                for(int a = 0; a < d_model; a++){
                    sum += X[i][j][a] * V[a][k];
                }
                V_dealed[i][j][k] = sum;
            }
        }
    }

    vector<vector<vector<vector<double>>>> Q_head(batch_size, vector<vector<vector<double>>>
    (num_heads, vector<vector<double>>(n, vector<double>(d_k, 0.0))));
    // for(int i = 0; i < batch_size; i++){
    //     for(int j = 0; j < n; j++){
    //         for(int d = 0; d < d_model; d++){
    //             int h = d / d_k, r = d % d_k;
    //             Q_head[i][h][j][r] = Q_dealed[i][j][d];
    //         }
    //     }
    // }
    vector<vector<vector<vector<double>>>> K_head(batch_size, vector<vector<vector<double>>>
    (num_heads, vector<vector<double>>(n, vector<double>(d_k, 0.0))));
    // for(int i = 0; i < batch_size; i++){
    //     for(int j = 0; j < n; j++){
    //         for(int d = 0; d < d_model; d++){
    //             int h = d / d_k, r = d % d_k;
    //             K_head[i][h][j][r] = K_dealed[i][j][d];
    //         }
    //     }
    // }
    vector<vector<vector<vector<double>>>> V_head(batch_size, vector<vector<vector<double>>>
    (num_heads, vector<vector<double>>(n, vector<double>(d_k, 0.0))));
    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < n; j++){
            for(int d = 0; d < d_model; d++){
                int h = d / d_k, r = d % d_k;
                Q_head[i][h][j][r] = Q_dealed[i][j][d];
                K_head[i][h][j][r] = K_dealed[i][j][d];
                V_head[i][h][j][r] = V_dealed[i][j][d];
            }
        }
    }

    double inv = 1.0 / sqrt(d_k);
    vector<vector<vector<vector<double>>>> out1(batch_size, vector<vector<vector<double>>>
    (num_heads, vector<vector<double>>(n, vector<double>(d_k, 0.0))));

    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < num_heads; j++){
            vector<vector<double>> score(n, vector<double>(n, 0.0));
            for(int a = 0; a < n; a++){
                for(int b = 0; b < n; b++){
                    double dot = 0.0;
                    for(int k = 0; k < d_k; k++){
                        dot += Q_head[i][j][a][k] * K_head[i][j][b][k];
                    }
                    score[a][b] = dot * inv;
                }
            }

            
            for(int a = 0; a < n; a++){
                double max_s = -1e10;
                for(int b = 0; b < n; b++){
                    if(b > a) score[a][b] = -1e9;
                    if(score[a][b] > max_s) max_s = score[a][b];
                }
                double sumexp = 0.0;
                vector<double> p(n, 0.0);
                for(int b = 0; b < n; b++){
                    double e = exp(score[a][b] - max_s);
                    p[b] = e;
                    sumexp += e;
                }
                for(int r = 0; r < d_k; r++){
                    double acc = 0.0;
                    for(int b = 0; b < n; b++){
                        double w = (sumexp == 0.0 ? 0.0 : p[b] / sumexp);
                        acc += w * V_head[i][j][b][r];
                    }
                    out1[i][j][a][r] = acc;
                }
            }
        }
    }

    vector<vector<vector<double>>> out2(batch_size, vector<vector<double>>(n, vector<double>(d_model, 0.0)));
    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < n; j++){
            for(int h = 0; h < num_heads; h++){
                for(int r = 0; r < d_k; r++){
                    int k = h * d_k + r;
                    out2[i][j][k] = out1[i][h][j][r];
                }
            }
        }
    }
    vector<vector<vector<double>>> ans(batch_size, vector<vector<double>>(n, vector<double>(d_model, 0.0)));
    for(int i = 0; i < batch_size; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < d_model; k++){
                double sum = 0.0;
                for(int a = 0; a < d_model; a++){
                    sum += out2[i][j][a] * W[a][k];
                }
                ans[i][j][k] = sum;
            }
        }
    }

    print3D(ans);

    return 0;
}