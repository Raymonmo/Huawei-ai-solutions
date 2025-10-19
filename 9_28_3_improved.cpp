#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

double round2(double x){
    return round(100 * x ) / 100;
}

double number(string& line, int& now){
    double num = 0.0;
    while(line[now] >= '0' && line[now] <= '9'){
        num = num * 10 + (line[now] - '0');
        now++;
    }
    if(line[now] == '.'){
        int time = 1;
        now++;
        while(line[now] >= '0' && line[now] <= '9'){
            num += pow(0.1, time) * (line[now] - '0');
            time++;
            now++;
        }
    }
    now--;
    return num;
}

void print3D(vector<vector<vector<double>>>& mat){
    bool first1 = true;
    cout<<'[';
    for(auto c1 : mat){
        if(first1) {
            first1 = false;
        } else {
            cout<<", ";
        }
        cout<<'[';
        bool first2 = true;
        for(auto c2 : c1){
            if(first2){
                first2 = false;
            } else {
                cout<<", ";
            }
            cout<<'[';
            bool first3 = true;
            for(auto c3 : c2){
                if(first3) first3 = false;
                else cout<<", ";
                cout<<fixed<<setprecision(2)<<round2(c3);
            }
            cout<<"]";
        }
        cout<<"]";
    }
    cout<<']';
}

void print2D(vector<vector<double>>& mat){
    for(auto c1 : mat){
        for(auto c2 : c1){
            cout<<c2<<endl;
        }
    }
}

vector<vector<double>> get2D(string& line, int& now){
    bool f2 = false, f3 = false;
    while(line[now] != '[') now++;
    vector<vector<double>> ans;
    vector<double> tmp1;
    int negative = 1;
    while(now){
        if(line[now] == '['){
            if(f2){
                f3 = true;
            } else {
                f2 = true;
            }  
        } else if(line[now] >= '0' && line[now] <= '9'){
            double num = number(line, now);
            tmp1.push_back(num * negative);
            num = 0.0;
            negative = 1;
        } else if(line[now] == '-') {
            negative = -1;
        } else if(line[now] == ']'){
            if(f3){
                f3 = false;
                ans.push_back(tmp1);
                tmp1 = {};
            } else {
                f2 = false;
                break;
            }
        }
        now++;
    }
    return ans;
}

vector<vector<vector<double>>> get3D(string& line, int& now){
    bool f1 = false, f2 = false, f3 = false;
    while(line[now] != '[') now++;
    vector<vector<vector<double>>> ans;
    vector<vector<double>> tmp2;
    vector<double> tmp1;
    int negative = 1;
    while(now){
        if(line[now] == '['){
            if(f1){
                if(f2){
                    f3 = true;
                } else {
                    f2 = true;
                }
            } else {
                f1 = true;
            }
        } else if(line[now] >= '0' && line[now] <= '9'){
            double num = number(line, now);
            tmp1.push_back(num * negative);
            num = 0.0;
            negative = 1;
        } else if(line[now] == '-') {
            negative = -1;
        } else if(line[now] == ']'){
            if(f3){
                f3 = false;
                tmp2.push_back(tmp1);
                tmp1 = {};
            } else {
                if(f2){
                    f2 = false;
                    ans.push_back(tmp2);
                    tmp2 = {};
                } else {
                    f3 = false;
                    break;
                }
            }
        }
        now++;
    }
    return ans;
}

vector<vector<double>> multi(vector<vector<double>>& mat1, const vector<vector<double>>& mat2){
    int m = mat1.size();
    int n = mat2[0].size();
    int l = mat2.size();
    vector<vector<double>> ans(m, vector<double> (n,0.0));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < l; k++){
                ans[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return ans;
}

vector<vector<double>> trans(const vector<vector<double>>& mat){
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<double>> ans (n, vector<double> (m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans[i][j] = mat[j][i];
        }
    }
    return ans;
}

vector<vector<vector<double>>> multi3D(vector<vector<vector<double>>>& mat1, vector<vector<double>>& mat2){
    int m = mat1.size();
    vector<vector<vector<double>>> ans;
    for(int i = 0; i < m; i++){
        vector<vector<double>> tmp = multi(mat1[i], mat2);
        ans.push_back(tmp);
    }
    return ans;
}

vector<vector<vector<vector<double>>>> segment4D(vector<vector<vector<double>>>& mat, int n){
    int batchs = mat.size();
    int seqs = mat[0].size();
    int d_model = mat[0][0].size();
    int d_k = d_model / n;

    vector<vector<vector<vector<double>>>> ans(batchs, vector<vector<vector<double>>>
    (n, vector<vector<double>> (seqs, vector<double> (d_k))));
    for(int i = 0; i < batchs; i++){
        for(int j = 0; j < seqs; j++){
            for(int k = 0; k < d_model; k++){
                int d1 = k / d_k;
                int d2 = k % d_k;
                ans[i][d1][j][d2] = mat[i][j][k];
            }
        }
    }
    return ans;
}

vector<vector<double>> softmax(vector<vector<double>>& mat){
    vector<vector<double>> ans = mat;
    for(int i = 0; i < mat.size(); i++){
        double max_num = mat[i][0];
        for(int j = 1; j < mat[0].size(); j++){
            max_num = max(max_num, mat[i][j]);
        }
        double sum = 0.0;
        for(int j = 0; j < mat[0].size(); j++){
            ans[i][j] = exp(ans[i][j] - max_num);
            sum += ans[i][j];
        }
        for(int j = 0; j < mat[0].size(); j++){
            ans[i][j] /= sum;
        }
    }
    return ans;
}

int main(){
    string line;
    getline(cin,line);
    int now = 0;
    char token = line[now];
    int n = number(line, now);
    
    vector<vector<vector<double>>> X = get3D(line, now);
    vector<vector<double>> wq = get2D(line, now);
    vector<vector<double>> wk = get2D(line, now);
    vector<vector<double>> wv = get2D(line, now);
    vector<vector<double>> wo = get2D(line, now);

    int batchs = X.size();
    int seqs = X[0].size();
    int d_model = X[0][0].size();
    int d_k = d_model / n;
    int d = wq.size();
    
    vector<vector<vector<double>>> Q = multi3D(X, wq);
    vector<vector<vector<double>>> K = multi3D(X, wk);
    vector<vector<vector<double>>> V = multi3D(X, wv);

    vector<vector<vector<vector<double>>>> Q_seg = segment4D(Q, n);
    vector<vector<vector<vector<double>>>> K_seg = segment4D(K, n);
    vector<vector<vector<vector<double>>>> V_seg = segment4D(V, n);

    vector<vector<vector<vector<double>>>> attention_scores (batchs, 
    vector<vector<vector<double>>> (n));

    for(int i = 0; i < batchs; i++){
        for(int j = 0; j < n; j++){
            vector<vector<double>> tmp = multi(Q_seg[i][j], trans(K_seg[i][j]));
            for(auto &c1 : tmp){
                for(auto &c2 : c1) c2 /= sqrt(d_k);
            }
            attention_scores[i][j] = tmp;
        }
    }

    vector<vector<double>> mask(seqs, vector<double> (seqs));
    for(int j = 0; j < seqs; j++){
        for(int k = 0; k < seqs; k++){
            if(j >= k){
                mask[j][k] = 0;
            } else {
                mask[j][k] = -100000000000000.0;
            }
        }
    }

    for (int i = 0; i < batchs; i++) {
        for (int j = 0; j < n; j++) {
            for (int row = 0; row < seqs; row++) {
                for (int col = 0; col < seqs; col++) {
                    attention_scores[i][j][row][col] += mask[row][col];
                }
            }
        }
    }   

    vector<vector<vector<vector<double>>>> soft_scores(batchs, vector<vector<vector<double>>> (n));
    for(int i = 0; i < batchs; i++){
        for(int j = 0; j < n; j++){
            soft_scores[i][j] = softmax(attention_scores[i][j]);
        }
    }

    vector<vector<vector<vector<double>>>> result(batchs, vector<vector<vector<double>>> (n));
    for(int i = 0; i < batchs; i++){
        for(int j = 0; j < n; j++){
            result[i][j] = multi(soft_scores[i][j], V_seg[i][j]);
        }
    }

    vector<vector<vector<double>>> input(batchs, vector<vector<double>> (seqs, vector<double> (d_model)));
    for(int i = 0; i < batchs; i++){
        for(int j = 0; j < seqs; j++){
            for(int k = 0; k < d_model; k++){
                int d1 = k / d_k;
                int d2 = k % d_k;
                input[i][j][k] = result[i][d1][j][d2];
            }
        }
    }

    vector<vector<vector<double>>> output(batchs);
    for(int i = 0; i < batchs; i++){
        output[i] = multi(input[i], wo);
    }

    print3D(output);

    return 0;
}