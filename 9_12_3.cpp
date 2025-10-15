#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <vector>
using namespace std;

double round4(double x){
    return round(x * 10000) / 10000;
}

void matrixMul(vector<vector<double>>& x, vector<vector<double>>& y, vector<vector<double>>& ans){
    int m = ans.size();
    int n = ans[0].size();
    int d = x[0].size();
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            ans[i][j] = 0;
            for(int k = 0; k < d; k++){
                ans[i][j] += x[i][k] * y[k][j];
            }
        }
    }
}

int main(){
    int b, d, r;
    cin >> b >> d >> r;

    // 读取输入矩阵 x
    vector<vector<double>> x(b, vector<double>(d));
    for(long long count = 0; count < b * d; count++){
        int i = count / d;
        int j = count % d;
        cin >> x[i][j];
    }

    // 读取权重矩阵 wq, wk, wv
    vector<vector<double>> wq(d, vector<double>(d));
    vector<vector<double>> wk(d, vector<double>(d));
    vector<vector<double>> wv(d, vector<double>(d));
    for(long long count = 0; count < d * d; count++){
        int i = count / d;
        int j = count % d;
        cin >> wq[i][j];
    }
    for(long long count = 0; count < d * d; count++){
        int i = count / d;
        int j = count % d;
        cin >> wk[i][j];
    }
    for(long long count = 0; count < d * d; count++){
        int i = count / d;
        int j = count % d;
        cin >> wv[i][j];
    }

    // 读取 LoRA 适配器参数
    if(r > 0){
        vector<vector<double>> A(r, vector<double>(d));
        vector<vector<double>> B(d, vector<double>(r));
        for(long long count = 0; count < r * d; count++){
            int i = count / d;
            int j = count % d;
            cin >> A[i][j];
        }
        for(long long count = 0; count < d * r; count++){
            int i = count / r;
            int j = count % r;
            cin >> B[i][j];
        }
        vector<vector<double>> C(d, vector<double>(d, 0));
        matrixMul(B, A, C);
        for(int i = 0; i < d; i++){
            for(int j = 0; j < d; j++){
                wq[i][j] += C[i][j];
            }
        }
    }

    // 计算 Q, K, V
    vector<vector<double>> wq_dealed(b, vector<double>(d, 0));
    vector<vector<double>> wk_dealed(b, vector<double>(d, 0));
    vector<vector<double>> wv_dealed(b, vector<double>(d, 0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            wq_dealed[i][j] = 0;
            for(int k = 0; k < d; k++){
                wq_dealed[i][j] += x[i][k] * wq[j][k];
            }
        }
    }
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            wk_dealed[i][j] = 0;
            for(int k = 0; k < d; k++){
                wk_dealed[i][j] += x[i][k] * wk[j][k];
            }
        }
    }
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            wv_dealed[i][j] = 0;
            for(int k = 0; k < d; k++){
                wv_dealed[i][j] += x[i][k] * wv[j][k];
            }
        }
    }

    // matrixMul(x, wq, wq_dealed);
    // matrixMul(x, wk, wk_dealed);
    // matrixMul(x, wv, wv_dealed);

    // 计算注意力分数 QKᵀ / sqrt(d)
    vector<vector<double>> soft1(b, vector<double>(b, 0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < b; j++){
            for(int k = 0; k < d; k++){
                soft1[i][j] += wq_dealed[i][k] * wk_dealed[j][k];
            }
            soft1[i][j] /= sqrt(double(d));
        }
    }

    // softmax
    vector<vector<double>> output1(b, vector<double>(b));
    for(int i = 0; i < b; i++){
        double maxNum = soft1[i][0];
        for(int j = 0; j < b; j++){
            maxNum = max(maxNum, soft1[i][j]);
        }
        double sum = 0;
        for(int j = 0; j < b; j++){
            soft1[i][j] = exp(soft1[i][j] - maxNum);
            sum += soft1[i][j];
        }
        for(int j = 0; j < b; j++){
            output1[i][j] = soft1[i][j] / sum;
        }
    }

    // 输出最终结果
    vector<vector<double>> ans(b, vector<double>(d, 0));
    matrixMul(output1, wv_dealed, ans);

    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            double v = round4(ans[i][j]);
            if(v == -0.0) v = 0.0; // 保证 -0.0000 输出为 0.0000
            if(i == 0 && j == 0){
                cout << fixed << setprecision(4) << v;
            } else {
                cout << " " << fixed << setprecision(4) << v;
            }
        }
    }

    return 0;
}
