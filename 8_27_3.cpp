#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

struct Node{
    Node* l = nullptr;
    Node* r = nullptr;
    int label;
    bool leaf = false;
    int f;
    int threshold;
    Node(int val1, int val2, int val3) : f(val1), threshold(val2), label(val3){}
};

double round6(double x){
    return round(x * 1e6) / 1e6;
}

double pre_cal(vector<int>& real, vector<int>& pred){
    double tp = 0, fp = 0;
    for(int i = 0; i < real.size(); i++){
        if(real[i] == 1 && pred[i] == 1) tp++;
        if(real[i] == 0 && pred[i] == 1) fp++;
    }
    if(tp + fp == 0) return 0.0;
    else return tp / (tp + fp);
}

double recall_cal(vector<int>& real, vector<int>& pred){
    double tp = 0, fn = 0;
    for(int i = 0; i < real.size(); i++){
        if(real[i] == 1 && pred[i] == 1) tp++;
        if(real[i] == 1 && pred[i] == 0) fn++;
    }
    if(tp + fn == 0) return 0.0;
    else return tp / (tp + fn);
}

double f1(vector<int>& real, vector<int>& pred){
    double precision = pre_cal(real, pred);
    double recall = recall_cal(real, pred);
    if(precision + recall == 0) return 0.0;
    return 2 * (precision * recall) / (precision + recall);
}

void buildTree(vector<vector<int>>& store, Node* root, int left, int right){
    Node* left_node = new Node(store[left][2], store[left][3], store[left][4]);
    root->l = left_node;
    if(store[left][0] == 0){
        left_node->leaf = true;
    } else {
        left_node->leaf = false;
        buildTree(store, left_node, store[left][0], store[left][1]);
    }

    Node* right_node = new Node(store[right][2], store[right][3], store[right][4]);
    root->r = right_node;
    if(store[right][0] == 0){
        right_node->leaf = true;
    } else {
        right_node->leaf = false;
        buildTree(store, right_node, store[right][0], store[right][1]);
    }
}

double max_f1 = 0.0;

double cut(Node* root, Node* cur, vector<vector<int>>& valid, vector<int>& idx){
    int m = valid.size();
    int k = valid[0].size() - 1;
    vector<int> leaf_pred(idx.size());
    vector<int> keep_pred(idx.size());
    vector<int> leaf_real(idx.size());
    for(int i = 0; i < idx.size(); i++){
        leaf_real[i] = valid[idx[i]][k];
        leaf_pred[i] = cur->label;
    }

    if(cur->leaf || idx.empty()){
        return f1(leaf_real, leaf_pred);
    }

    vector<int> L, R;
    for(int t : idx){
        if(valid[t][cur->f-1] <= cur->threshold) L.push_back(t);
        else R.push_back(t);
    }
    double f1_left = cur->l ? cut(root, cur->l, valid, L) : 0.0;
    double f1_right = cur->r ? cut(root, cur->r, valid, R) : 0.0;
    vector<int> keep_real(idx.size());

    for(int i = 0; i < idx.size(); i++){
        int t = idx[i];
        Node* state = cur;
        while(!state->leaf){
            if(valid[t][state->f-1] > state->threshold) state = state->r;
            else state = state->l;

            if(!state) break;
        }

        keep_pred[i] = state ? state->label : cur->label;
        keep_real[i] = valid[t][k];
    }

    double f1_keep = f1(keep_real, keep_pred);

    if(f1(leaf_real, leaf_pred) >= f1_keep) cur->leaf = true;

    return max(f1(leaf_real, leaf_pred), f1_keep);

    // int M = valid.size();
    // int K = valid[0].size() - 1;
    // vector<int> pred(M,0);
    // vector<int> real(M,0);
    // for(int i = 0; i < M; i++){
    //     real[i] = valid[i][K];
    //     Node* state = root;
    //     while(1){
    //         if(state == cur || state->leaf){
    //             pred[i] = state->label;
    //             break;
    //         }
    //         if(valid[i][state->f-1] > state->threshold){
    //             state = state->r;
    //         } else {
    //             state = state->l;
    //         }
    //     }
    // }
    // double now_f1 = f1(real, pred);
    // for(int i = 0; i < M; i++){
    //     real[i] = valid[i][K];
    //     Node* state = root;
    //     while(1){
    //         if(state->leaf){
    //             pred[i] = state->label;
    //             break;
    //         }
    //         if(valid[i][state->f-1] > state->threshold){
    //             state = state->r;
    //         } else {
    //             state = state->l;
    //         }
    //     }
    // }
    // double pre_f1 = f1(real, pred);
    // //if(now_f1 >= pre_f1) cur->leaf = true;
    // max_f1 = max(max_f1, now_f1);
    
}

int main(){
    int N,M,K;
    cin >> N >> M >> K;
    vector<vector<int>> store(N+1, vector<int>(5));
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < 5; j++){
            cin >> store[i][j];
        }
    }
    
    Node* root = new Node(store[1][2], store[1][3], store[1][4]);
    if(store[1][0] == 0) root->leaf = true;
    else {
        root->leaf = false;
        buildTree(store, root, store[1][0], store[1][1]);
    }

    vector<vector<int>> valid(M, vector<int>(K+1));
    for(int i = 0; i < M; i++){
        for(int j = 0; j <= K; j++){
            cin >> valid[i][j];
        }
    }
    vector<int> all(M); iota(all.begin(), all.end(), 0);
    if(M > 0 && K > 0) max_f1 = cut(root, root, valid, all);

    cout << fixed << setprecision(6) << round6(max_f1) << endl;
    return 0;
}
