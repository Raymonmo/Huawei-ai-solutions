#include <bits/stdc++.h>
using namespace std;

void printMat(const vector<vector<double>>& mat){
    for(auto c : mat){
        for(auto x : c){
            cout<<x<<" ";
        }
        cout<<endl;
    }
}

double sum(const vector<vector<double>>& mat){
    double ans = 0.0;
    for(auto c : mat){
        for(auto x : c){
            ans += x;
        }
    }
    return ans;
}

vector<vector<double>> softmax(const vector<vector<double>>& mat, double d){
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<double>> ans = mat;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            ans[i][j] = ans[i][j] / sqrt(d);
        }
    }   
    for(int i = 0; i < m; i++){
        double sum = 0.0;
        for(int j = 0; j < n; j++){
            sum += ans[i][j];
        }
        for(int j = 0; j < n; j++){
            ans[i][j] = ans[i][j] / sum;
        }
    }
    return ans;
}

vector<vector<double>> multi(const vector<vector<double>>& mat1, const vector<vector<double>>& mat2){
    int m = mat1.size();
    int n = mat2[0].size();
    int k = mat2.size();
    vector<vector<double>> ans(m, vector<double> (n,0));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int x = 0; x < k; x++){
                ans[i][j] += mat1[i][x] * mat2[x][j];
            }
        }
    }
    return ans;
}

vector<vector<double>> trans(const vector<vector<double>>& mat){
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<double>> ans(n, vector<double> (m,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans[i][j] = mat[j][i];
        }
    }
    return ans;
}

int main(){
    int n, m, h;
    cin>>n>>m>>h;
    vector<vector<double>> x(n, vector<double> (m,1.0));

    vector<vector<double>> wq(m, vector<double> (h, 0.0));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < h; j++){
            if(i <= j) wq[i][j] = 1.0;
        }
    }

    vector<vector<double>> wk = wq, wv = wq;

    vector<vector<double>> Q = multi(x, wq);
    vector<vector<double>> K = multi(x, wk);
    vector<vector<double>> V = multi(x, wv);

    vector<vector<double>> Y = multi(softmax(multi(Q, trans(K)), h), V);

    cout<<round(sum(Y));

    return 0;
}