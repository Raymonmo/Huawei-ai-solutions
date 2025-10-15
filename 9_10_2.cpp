#include <bits/stdc++.h>
using namespace std;

/**
 * 按空白分词（保留大小写），窗口内 TF-IDF + 余弦相似度（仅分子加权），
 * 阈值0.6，分数并列取更早的文档（编号更小）。
 */

// 将一行按任意空白分词（保留大小写）
static vector<string> splitWords(const string& s0) {
    vector<string> res;
    string s = s0;
    int n = (int)s.size();
    int i = 0;
    while (i < n) {
        while (i < n && isspace((unsigned char)s[i])) i++; // 跳过空白
        if (i >= n) break;
        int j = i;
        while (j < n && !isspace((unsigned char)s[j])) j++; // 读一个词
        res.emplace_back(s.substr(i, j - i));
        i = j;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    // 读 N
    getline(cin, line);
    int N = stoi(line);

    // 读文档原文
    vector<string> raws(N);
    for (int i = 0; i < N; ++i) {
        getline(cin, raws[i]);
        if (!raws[i].empty() && raws[i].back() == '\r') raws[i].pop_back(); // 处理 \r
    }

    getline(cin, line);
    int K = stoi(line);
    getline(cin, line);
    int P = stoi(line);

    // 预处理：每篇文档的词频与长度
    vector<unordered_map<string,int>> dcnt(N);
    vector<int> dlen(N);
    for (int i = 0; i < N; ++i) {
        vector<string> tks = splitWords(raws[i]);
        dlen[i] = (int)tks.size();
        auto &mp = dcnt[i];
        for (auto &w : tks) mp[w]++;
    }

    vector<int> answers;
    answers.reserve(P);

    for (int qi = 0; qi < P; ++qi) {
        getline(cin, line);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        // 解析 t 与查询串（查询可能为空）
        auto sp = line.find(' ');
        int t = stoi(sp == string::npos ? line : line.substr(0, sp));
        vector<string> qWords = (sp == string::npos) ? vector<string>() : splitWords(line.substr(sp + 1));

        // 窗口 [L, R]
        int R = min(max(0, t), N - 1);
        int L = max(0, R - K + 1);
        int M = R - L + 1;

        if (qWords.empty() || M <= 0) {
            answers.push_back(-1);
            continue;
        }

        // 查询词频与长度
        unordered_map<string,int> qcnt;
        for (auto &w : qWords) qcnt[w]++;
        int qlen = (int)qWords.size();

        // df & idf（仅查询词）
        unordered_map<string,int> df;
        for (auto &kv : qcnt) df[kv.first] = 0;

        for (int i = L; i <= R; ++i) {
            auto &dm = dcnt[i];
            for (auto &kv : qcnt) {
                const string &w = kv.first;
                if (dm.find(w) != dm.end()) df[w]++;
            }
        }

        unordered_map<string,double> idf;
        for (auto &kv : qcnt) {
            const string &w = kv.first;
            double v = log((M + 1.0) / (df[w] + 1.0)) + 1.0; // 平滑IDF
            idf[w] = v;
        }

        // 查询向量范数
        double qnorm2 = 0.0;
        for (auto &kv : qcnt) {
            const string &w = kv.first;
            double tfq = kv.second * 1.0 / qlen;
            double x = tfq * idf[w];
            qnorm2 += x * x;
        }
        double qnorm = qnorm2 > 0 ? sqrt(qnorm2) : 1.0;

        double bestScore = -1.0;
        int bestId = -1;

        // 新->旧遍历，便于计算 j
        for (int idx = R; idx >= L; --idx) {
            int dl = dlen[idx] > 0 ? dlen[idx] : 1;
            auto &dm = dcnt[idx];

            double dot = 0.0, dnorm2 = 0.0;

            // 只遍历查询词
            for (auto &kv : qcnt) {
                const string &w = kv.first;
                int cdoc = 0;
                auto it = dm.find(w);
                if (it != dm.end()) cdoc = it->second;

                double tfd = cdoc * 1.0 / dl;           // 文档内词频
                double tfq = kv.second * 1.0 / qlen;     // 查询内词频
                double dq = tfq * idf[w];
                double dd = tfd * idf[w];
                dot += dq * dd;
                dnorm2 += dd * dd;
            }

            double sim = 0.0;
            if (dnorm2 > 0) {
                double dnorm = sqrt(dnorm2);
                int j = (R - idx) + 1;                 // 最新位置 j=1
                double weight = (K - j + 1.0) / K;     // 动态权重（假设 K>=1）
                sim = (dot * weight) / (qnorm * dnorm); // 仅分子加权
            }

            // 阈值与并列规则（更早编号优先）
            if (sim >= 0.6 - 1e-12) {
                if (sim > bestScore + 1e-12) {
                    bestScore = sim; bestId = idx;
                } else if (fabs(sim - bestScore) <= 1e-12) {
                    if (bestId == -1 || idx < bestId) bestId = idx;
                }
            }
        }

        answers.push_back(bestId == -1 ? -1 : bestId);
    }

    // 输出
    for (int i = 0; i < (int)answers.size(); ++i) {
        if (i) cout << ' ';
        cout << answers[i];
    }
    return 0;
}

