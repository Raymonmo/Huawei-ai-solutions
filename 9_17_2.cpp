#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m, h;
    cin>>n>>m>>h;

    vector<vector<int>> X (n, vector<int> (m,1));
    vector<vector<int>> W1 (m, vector<int> (h,0));
    for(int i = 0; i < m; i++){
        for(int j = i; j < h; j++){
            W1[i][j] = 1;
        }
    }
    vector<vector<int>> W2 (m, vector<int> (h,0));
    for(int i = 0; i < m; i++){
        for(int j = i; j < h; j++){
            W2[i][j] = 1;
        }
    }
    vector<vector<int>> W3 (m, vector<int> (h,0));
    for(int i = 0; i < m; i++){
        for(int j = i; j < h; j++){
            W3[i][j] = 1;
        }
    }
    vector<vector<int>> Q(n, vector<int> (h,0));
    vector<vector<int>> K(n, vector<int> (h,0));
    vector<vector<int>> V(n, vector<int> (h,0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < h; j++){
            for(int k = 0; k < m; k++){
                Q[i][j] += X[i][k] * W1[k][j];
                K[i][j] += X[i][k] * W2[k][j];
                V[i][j] += X[i][k] * W3[k][j];
            }
        }
    }

    vector<vector<double>> out1(n, vector<double> (n,0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < h; k++){
                out1[i][j] += Q[i][k] * K[j][k];
            }
            out1[i][j] /= sqrt(h);
        }
    }
    for(int i = 0; i < n; i++){
        double sum = 0;
        for(int j = 0; j < n; j++){
            sum += out1[i][j];
        }
        for(int j = 0; j < n; j++){
            out1[i][j] /= sum;
        }
    }
    vector<vector<double>> out2(n, vector<double> (h,0));
    double ans = 0.0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < h; j++){
            for(int k = 0; k < n; k++){
                out2[i][j] += out1[i][k] * V[k][j];
            }
            ans += out2[i][j];
        }
    }
    cout<<round(ans);
    return 0;
}