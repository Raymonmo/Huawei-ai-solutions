#include <bits/stdc++.h>
#include <sstream>
using namespace std;

struct Node{
    Node* l = nullptr;
    Node* r = nullptr;
    Node* parent = nullptr;
    int val;
    Node(int v) : val(v){}
};

Node* buildTree(vector<string>& vec){
    Node* root = new Node(stoi(vec[0]));
    int now = 1;
    queue<pair<Node*, int>> q;
    q.push({root,0});
    q.push({root,1});
    while(now < vec.size()){
        if(vec[now] == "#"){
            q.pop();
        } else {
            int value = stoi(vec[now]);
            auto x = q.front();
            q.pop();
            if(x.second == 0){
                Node* left = new Node(value);
                left->parent = x.first;
                x.first->l = left;
                q.push({left,0});
                q.push({left,1});
            } else {
                Node* right = new Node(value);
                right->parent = x.first;
                x.first->r = right;
                q.push({right,0});
                q.push({right,1});
            }
        }
        now++;
    }
    return root;
}

Node* dfs(Node* root, int u){
    if(root){
        if(root->val == u) return root;
        Node* left = dfs(root->l, u);
        Node* right = dfs(root->r, u);
        if(left) return left;
        if(right) return right;
    }
    return nullptr;
}

int find(Node* root, int u, int k){
    Node* tar = dfs(root, u);
    int ans = -1;

    Node* cur = tar;
    vector<Node*> kparents;
    while(cur){
        if(cur->parent && cur->parent->r == cur) kparents.push_back(cur->parent);
        cur = cur->parent;
    }
    if(k > kparents.size()){
        ans = -1;
    } else {
        ans = kparents[kparents.size() - k]->val;
    }
    return ans;
}

int main(){
    string line;
    getline(cin,line);
    vector<string> vec;
    stringstream ss(line);
    string token;
    while(ss>>token){
        vec.push_back(token);
    }
    Node* root = buildTree(vec);
    
    int u, k;
    cin>>u>>k;

    cout<<find(root, u ,k);

    return 0;
}