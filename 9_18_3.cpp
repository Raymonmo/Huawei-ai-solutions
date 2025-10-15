#include <bits/stdc++.h>
#include <type_traits>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    vector<int> classify(k);
    long long N = 0;
    for(int i = 0; i < k; i++){
        cin>>classify[i];
        N += classify[i];
    }
    int m;
    cin>>m;
    vector<vector<vector<float>>> train;
    for(int i = 0; i < k; i++){
        vector<vector<float>> record;
        for(int j = 0; j < classify[i]; j++){
            vector<float> record2;
            for(int a = 0; a < n; a++){
                float now;
                cin>>now;
                record2.push_back(now);
            }
            record.push_back(record2);
        }
        train.push_back(record);
    }

    vector<vector<float>> predict(m, vector<float> (n));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cin>>predict[i][j];
        }
    }

    //特征标准化
    const float eps = 1e-8;
    vector<float> mu(n, 0.0);
    vector<float> sigma(n, 0.0);
    for(int i = 0; i < n; i++){
        float s = 0.0;
        for(int j = 0; j < k; j++){
            for(int a = 0; a < classify[j]; a++){
                s += train[j][a][i];
            }   
        }
        //对每个样本的某一位置的参数求和并标准化
        mu[i] = s / N;
    }
    for(int i = 0; i < n; i++){
        float ss = 0.0;
        for(int j = 0; j < k; j++){
            for(int a = 0; a < classify[j]; a++){
                float d = train[j][a][i] - mu[i];
                ss += d * d;
            }
        }
        //标准差
        sigma[i] = sqrt(ss / max(1LL, N - 1));
    }

    //对训练集和测试集都进行标准化
    for(int i = 0; i < k; i++){
        for(int j = 0; j < classify[i]; j++){
            for(int a = 0; a < n; a++){
                train[i][j][a] = (train[i][j][a] - mu[a]) / (sigma[a] + eps);
            }
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            predict[i][j] = (predict[i][j] - mu[j]) / (sigma[j] + eps);
        }
    }

    //参数初始化
    vector<vector<float>> w(n, vector<float> (k, 0.1));
    vector<float> b(k, 0);
    float lr = 0.1;
    int iteration = 1000;
    float reg = 1e-4;  //正则化系数，防止权重过大

    //逻辑回归与概率
    vector<float> logits(k), probs(k);

    for(int epoch = 0; epoch < iteration; epoch++){

        //梯度
        vector<vector<float>> dw(n, vector<float>(k, 0.0));
        vector<float> db(k, 0.0);

        //i和j是对训练样本的循环
        for(int i = 0; i < k; i++){
            for(int j = 0; j < classify[i]; j++){

                //g是对每个标签的循环，用于使用w计算当前的得分
                for(int g = 0; g < k; g++){
                    float s = b[g];
                    //a是对特征的循环，用于累加乘积，模拟矩阵乘法
                    for(int a = 0; a < n; a++){
                        s += train[i][j][a] * w[a][g];
                    }
                    //logits为O
                    logits[g] = s;
                }
                //mx为最大概率，softmax中进行处理
                float mx = logits[0];
                for(int g = 1; g < k; g++){
                    mx = max(mx, logits[g]);
                }
                //sumexp用于计算总体概率
                double sumExp = 0.0;
                for(int g = 0; g < k; g++){
                    probs[g] = exp(logits[g] - mx);
                    sumExp += probs[g];
                }
                for(int g = 0; g < k; g++){
                    //使得概率总和为1
                    probs[g] /= (sumExp + eps);
                }

                //当前样本标签
                int y = i;
                for(int g = 0; g < k; g++){
                    //diff为损失函数，交叉熵损失对logits的梯度，P-Y
                    float diff = probs[g] - (g == y ? 1.0 : 0.0);
                    for(int f = 0; f < n; f++){
                        //dw是用X的转置
                        dw[f][g] += train[i][j][f] * diff;
                    }
                    db[g] += diff;
                }
            }
        }
        float invN = (N ? 1.0 / (float)N : 1.0); //归一化因子，相当于/m

        //完整的梯度计算
        for(int f = 0; f < n; f++){
            for(int g = 0; g < k; g++){
                dw[f][g] = dw[f][g] * invN + reg * w[f][g];
            }
        }
        for(int g = 0; g < k; g++) db[g] *= invN;

        //参数更新
        for(int f = 0; f < n; f++){
            for(int g = 0; g < k; g++){
                w[f][g] -= lr * dw[f][g];
            }
        }
        for(int g = 0; g < k; g++){
            b[g] -= db[g] * lr;
        }
        //学习率调整
        if((epoch + 1) % 150 == 0) lr *= 0.9;
    }

    //预测
    for(int i = 0; i < m; i++){
        //对每个样本
        for(int j = 0; j < k; j++){
            //对每个类别计算，得到当前类别的预测概率
            float s = b[j];
            //对每个特征进行累加
            for(int f = 0; f < n; f++){
                s += predict[i][f] * w[f][j];
            }
            //总的概率
            logits[j] = s;
        }
        //取出最大概率的类别为预测类别
        int argmax = 0;
        for(int j = 1; j < k; j++){
            if(logits[j] > logits[argmax]) argmax = j;
        }
        cout<<argmax<<endl;
    }
    return 0;
}