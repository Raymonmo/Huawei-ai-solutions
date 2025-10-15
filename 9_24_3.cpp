#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct treeNode{
    treeNode* left = nullptr;
    treeNode* right = nullptr;
    int character;
    int threshold;
    bool leaf = false;
    treeNode(): character(0), threshold(-1) {}
};

double cal_H(int state, int n){
    double p = double(state) / n;
    return -p * log(p);
}

double entropy(vector<int>& label){
    double ans = 0.0;
    int n = label.size();
    if(n == 0) return ans;
    int c1 = 0;
    for(int i = 0; i < n; i++){
        c1 += label[i];
    }
    int c0 = n - c1;
    if(c0 > 0){
        ans += cal_H(c0, n);
    }
    if(c1 > 0){
        ans += cal_H(c1, n);
    }
    
    return ans;
}

int majorLabel(vector<int>& label){
    int c1 = 0;
    for(int c : label){
        c1 += c;
    }
    int c0 = (int)label.size() - c1;
    return (c1 > c0) ? 1 : 0;
}

treeNode* buildTree(vector<vector<int>>& characters, vector<int>& label, 
                    vector<int>& idx, vector<int>& used){
    int n = characters.size();
    bool pure = true;
    for(int id : idx){
        if(label[id] != label[idx[0]]){
            pure = false;
            break;
        }
    }

    if(pure){
        treeNode* leaf = new treeNode();
        leaf->leaf = true;
        leaf->character = label[idx[0]];
        return leaf;
    }

    vector<int> labels;
    for(int id : idx){
        labels.push_back(label[id]);
    }

    double baseH = entropy(labels);
    double bestG = -1.0, eps = 1e-12;
    int bestF = -1;
    int m = characters[0].size();

    for(int f = 0; f < m; f++){
        if(used[f]) continue;

        vector<int> lab0, lab1;
        for(int id : idx){
            if(characters[id][f] == 0){
                lab0.push_back(label[id]);
            } else {
                lab1.push_back(label[id]);
            }
        }

        double H = (lab0.size() * 1.0 / idx.size()) * entropy(lab0)
                    + (lab1.size() * 1.0 / idx.size()) * entropy(lab1);
        double gain = baseH - H;
        if(gain > bestG + eps || (fabs(gain - bestG) <= eps && f < bestF)){
            bestG = gain;
            bestF = f;
        }
    }

    if(bestF == -1 || bestG <= eps){
        treeNode* leaf = new treeNode();
        leaf->leaf = true;
        leaf->character = majorLabel(labels);
        return leaf;
    }

    vector<int> idx0, idx1;

    for(int id : idx){
        if(characters[id][bestF] == 0){
            idx0.push_back(id);
        } else {
            idx1.push_back(id);
        }
    }

    treeNode* cur = new treeNode();
    cur->leaf = false;
    cur->threshold = bestF;
    used[bestF] = 1;

    if(idx0.empty()){
        treeNode* rf = new treeNode();
        rf->leaf = true;
        rf->character = majorLabel(labels);
        cur->left = rf;
    } else cur->left = buildTree(characters, label, idx0, used);
    if (idx1.empty()) {
        treeNode* rf = new treeNode();
        rf->leaf = true;
        rf->character = majorLabel(labels);
        cur->right = rf;
    } else cur->right = buildTree(characters, label, idx1, used);
    used[bestF] = 0;

    return cur;
}

int predict(treeNode* root, vector<int> tar){
    treeNode* p = root;
    while(!p->leaf){
        p = (tar[p->threshold] == 0 ? p->left : p->right);
    }
    return p->character;
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> label(n);
    vector<vector<int>> characters(n, vector<int> (m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>characters[i][j];
        }
        cin>>label[i];
    }
    vector<int> idx(n);
    for(int i = 0; i < n; i++){
        idx[i] = i;
    }
    vector<int> used(m,0);
    treeNode* root = buildTree(characters, label, idx, used);

    int q;
    cin>>q;
    for(int i = 0; i < q; i++){
        vector<int> query(m);
        for(int j = 0; j < m; j++){
            cin>>query[j];
        }
        cout<<predict(root, query)<<endl;
    }
    return 0;
}