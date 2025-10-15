#include <bits/stdc++.h>
#include <cwchar>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Node{
    int v;
    Node *l, *r;
    Node(int _v): v(_v), l(NULL), r(NULL) {}
};

struct buildResult{
    Node* root;
    unordered_map<Node*, Node*> parent;
    unordered_map<int, Node*> val2node;
};

buildResult buildTree(vector<int>& treeNum){
    buildResult res;
    res.root = NULL;
    queue<Node*> q;
    res.root = new Node(treeNum[0]);
    q.push(res.root);
    int count = 1;
    while(!q.empty() && count < treeNum.size()){
        Node* now = q.front();
        q.pop();
        if(now->v != -1){
            if(count < treeNum.size()){
                Node* left = new Node(treeNum[count]);
                now->l = left;
                res.val2node.insert({treeNum[count],left});
                res.parent.insert({left,now});
                q.push(left);
            }
            count++;
            if(count < treeNum.size()){
                Node* right = new Node(treeNum[count]);
                now->r = right;
                right->v = treeNum[count];
                res.val2node.insert({treeNum[count],right});
                res.parent.insert({right,now});
                q.push(right);
            }
            count++;
        } else {
            continue;
        }
    }
    return res;
}

int kAncent(buildResult treeRoot, int u, int k){
    Node* rootNow = treeRoot.root;
    unordered_map<Node*, Node*> parent = treeRoot.parent;
    unordered_map<int, Node*> val2node = treeRoot.val2node;
    if(!val2node.count(u)) return -1;
    Node* origin = val2node[u];
    Node* now = origin;
    Node* pre = origin;
    queue<Node*> ancent;
    while(now != rootNow){
        now = parent[now];
        if(now->r == pre){
            ancent.push(now);
        }
        if(ancent.size() > k){
            ancent.pop();
        }
        pre = now;
    }
    if(ancent.size() == k){
        return ancent.front()->v;
    } else {
        return -1;
    }
}

int main(){
    string line;
    getline(cin,line);
    stringstream ss(line);
    vector<int> tree;
    string token;
    while(getline(ss,token,' ')){
        if(token != "#"){
            tree.push_back(stoi(token));
        } else {
            tree.push_back(0-1);
        }
    }
    buildResult treeRoot = buildTree(tree);
    long long u,k;
    cin>>u>>k;
    int ans = kAncent(treeRoot, u, k);
    cout<<ans<<endl;
    return 0;
}