#include <bits/stdc++.h>
using namespace std;

// 解析二维数组，如 [[1,2],[3,4]]
static vector<vector<double>> parse2D(const string &s) {
    vector<vector<double>> res;
    vector<double> row;
    int depth = 0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '[') {
            depth++;
            if (depth == 2) row.clear();
        } else if (c == ']') {
            if (depth == 2) {
                if (!row.empty()) res.push_back(row);
                row.clear();
            }
            depth--;
        } else {
            // 读取数字
            if (isdigit(c) || c=='-' || c=='+' || c=='.' || c=='e' || c=='E') {
                int j = i;
                while (j < n && (isdigit(s[j]) || s[j]=='-' || s[j]=='+' || s[j]=='.' || s[j]=='e' || s[j]=='E')) j++;
                double val = stod(s.substr(i, j - i));
                row.push_back(val);
                i = j - 1;
            }
        }
    }
    return res;
}

// 解析三维数组，如 [[[...],[...]], [[...],[...]]]
static vector<vector<vector<double>>> parse3D(const string &s) {
    vector<vector<vector<double>>> res;
    vector<vector<double>> mat;
    vector<double> row;
    int depth = 0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '[') {
            depth++;
            if (depth == 2) mat.clear();
            if (depth == 3) row.clear();
        } else if (c == ']') {
            if (depth == 3) {
                if (!row.empty()) mat.push_back(row);
                row.clear();
            } else if (depth == 2) {
                if (!mat.empty()) res.push_back(mat);
                mat.clear();
            }
            depth--;
        } else {
            // 读取数字
            if (isdigit(c) || c=='-' || c=='+' || c=='.' || c=='e' || c=='E') {
                int j = i;
                while (j < n && (isdigit(s[j]) || s[j]=='-' || s[j]=='+' || s[j]=='.' || s[j]=='e' || s[j]=='E')) j++;
                double val = stod(s.substr(i, j - i));
                row.push_back(val);
                i = j - 1;
            }
        }
    }
    return res;
}

// X[b][t][d] * W[d][d] -> Y[b][t][d]
static vector<vector<vector<double>>> matmul3D2D(
    const vector<vector<vector<double>>> &X,
    const vector<vector<double>> &W) {
    int B = (int)X.size();
    int T = (int)X[0].size();
    int D = (int)X[0][0].size();
    vector<vector<vector<double>>> Y(B, vector<vector<double>>(T, vector<double>(D, 0.0)));
    for (int b = 0; b < B; ++b) {
        for (int t = 0; t < T; ++t) {
            for (int j = 0; j < D; ++j) {
                double sum = 0.0;
                for (int k = 0; k < D; ++k) sum += X[b][t][k] * W[k][j];
                Y[b][t][j] = sum;
            }
        }
    }
    return Y;
}

// 打印三维数组，保留两位小数
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

int main() {
    // 读取整份输入（可能包含空格与换行）
    std::ostringstream oss;
    string line;
    while (std::getline(cin, line)) {
        oss << line;
    }
    string all = oss.str();

    // 以分号拆分为6段：num_heads ; X ; W_Q ; W_K ; W_V ; W_O
    vector<string> parts;
    {
        string cur;
        for (char c : all) {
            if (c == ';') {
                parts.push_back(cur);
                cur.clear();
            } else {
                cur.push_back(c);
            }
        }
        if (!cur.empty()) parts.push_back(cur);
    }
    if (parts.size() != 6) return 0;

    // 解析num_heads
    int num_heads = 0;
    {
        string s = parts[0];
        // 用替换字符+输入流：将非数字转空格
        for (char &c : s) if (!(isdigit(c) || c=='-' || c=='+')) c = ' ';
        istringstream iss(s);
        iss >> num_heads;
    }

    // 解析X与四个权重
    auto X  = parse3D(parts[1]);
    auto WQ = parse2D(parts[2]);
    auto WK = parse2D(parts[3]);
    auto WV = parse2D(parts[4]);
    auto WO = parse2D(parts[5]);

    int B = (int)X.size();
    int T = (int)X[0].size();
    int D = (int)X[0][0].size();
    int H = num_heads;
    int d_k = D / H;

    // 1) 生成Q/K/V
    auto Q = matmul3D2D(X, WQ);
    auto K = matmul3D2D(X, WK);
    auto V = matmul3D2D(X, WV);

    // 2) 重排为多头 [B,H,T,d_k]
    auto to_heads = [&](const vector<vector<vector<double>>> &A){
        vector<vector<vector<vector<double>>>> Ah(
            B, vector<vector<vector<double>>>(H, vector<vector<double>>(T, vector<double>(d_k, 0.0)))
        );
        for (int b = 0; b < B; ++b)
            for (int t = 0; t < T; ++t)
                for (int d = 0; d < D; ++d) {
                    int h = d / d_k, r = d % d_k;
                    Ah[b][h][t][r] = A[b][t][d];
                }
        return Ah;
    };
    auto Qh = to_heads(Q);
    auto Kh = to_heads(K);
    auto Vh = to_heads(V);

    // 3-6) 注意力(带因果mask)
    double inv_sqrt = 1.0 / sqrt((double)d_k);
    vector<vector<vector<vector<double>>>> Ah( // attention后的值 [B,H,T,d_k]
        B, vector<vector<vector<double>>>(H, vector<vector<double>>(T, vector<double>(d_k, 0.0)))
    );

    for (int b = 0; b < B; ++b) {
        for (int h = 0; h < H; ++h) {
            // 预计算 scores [T][T]
            vector<vector<double>> scores(T, vector<double>(T, 0.0));
            for (int i = 0; i < T; ++i) {
                for (int j = 0; j < T; ++j) {
                    double dot = 0.0;
                    for (int r = 0; r < d_k; ++r) dot += Qh[b][h][i][r] * Kh[b][h][j][r];
                    scores[i][j] = dot * inv_sqrt;
                }
            }
            // softmax with causal mask
            for (int i = 0; i < T; ++i) {
                double maxv = -1e100;
                for (int j = 0; j < T; ++j) {
                    if (j > i) scores[i][j] = -1e9; // mask未来位置
                    if (scores[i][j] > maxv) maxv = scores[i][j];
                }
                double sumexp = 0.0;
                vector<double> p(T, 0.0);
                for (int j = 0; j < T; ++j) {
                    double e = exp(scores[i][j] - maxv);
                    p[j] = e;
                    sumexp += e;
                }
                // attention * V
                for (int r = 0; r < d_k; ++r) {
                    double acc = 0.0;
                    for (int j = 0; j < T; ++j) {
                        double w = (sumexp == 0.0 ? 0.0 : p[j] / sumexp);
                        acc += w * Vh[b][h][j][r];
                    }
                    Ah[b][h][i][r] = acc;
                }
            }
        }
    }

    // 7) 拼接头 -> [B,T,D]
    vector<vector<vector<double>>> concat(B, vector<vector<double>>(T, vector<double>(D, 0.0)));
    for (int b = 0; b < B; ++b)
        for (int t = 0; t < T; ++t)
            for (int h = 0; h < H; ++h)
                for (int r = 0; r < d_k; ++r)
                    concat[b][t][h*d_k + r] = Ah[b][h][t][r];

    // 线性投影 WO
    auto Y = matmul3D2D(concat, WO);

    // 输出
    print3D(Y);
    return 0;
}
