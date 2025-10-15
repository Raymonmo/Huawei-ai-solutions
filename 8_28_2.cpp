#include <iostream>
#include <vector>
using namespace std;

// 定义节点结构体
struct Node {
    int feature_index; // 分裂特征下标
    float threshold;   // 分裂阈值
    int left;          // 左子节点行号
    int right;         // 右子节点行号
    int label;         // 分类结果
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int f, m, n;
    cin >> f >> m >> n;

    vector<Node> tree(m);
    // 读取决策树节点信息
    for (int i = 0; i < m; i++) {
        cin >> tree[i].feature_index >> tree[i].threshold
            >> tree[i].left >> tree[i].right >> tree[i].label;
    }

    // 对每个样本进行推理
    for (int i = 0; i < n; i++) {
        vector<float> features(f);
        for (int j = 0; j < f; j++) {
            cin >> features[j];
        }
        int current = 0; // 从根节点开始
        while (tree[current].feature_index != -1) {
            // 根据阈值选择左右子节点
            if (features[tree[current].feature_index] <= tree[current].threshold) {
                current = tree[current].left;
            } else {
                current = tree[current].right;
            }
        }
        cout << tree[current].label << "\n";
    }
    return 0;
}
