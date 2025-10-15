#include <bits/stdc++.h>
#include <sstream>
using namespace std;

double norm(vector<double>& vec){
    double sum = 0.0;
    for(auto c : vec) sum += c * c;

    return sqrt(sum);
}
int main(){
    int N;
    cin>>N;
    cin.ignore();
    vector<vector<string>> files;
    vector<unordered_map<string, int>> stores;
    for(int i = 0; i < N; i++){
        vector<string> file;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        unordered_map<string, int> store;
        while(ss>>token){
            file.push_back(token);
            store[token]++;
        }
        files.push_back(file);
        stores.push_back(store);
    }

    int K, P;
    cin>>K>>P;
    cin.ignore();

    bool first = true;
    while(P--){
        vector<string> query;
        string line;
        getline(cin, line);
        stringstream ss(line);
        string token;
        int start;
        ss>>start;
        unordered_map<string, int> store;
        while(ss>>token){
            query.push_back(token);
            store[token]++;
        }

        int m = store.size();

        int R = min(N-1, max(start,0));
        int L = max(R - K + 1, 0);
        int len = R - L + 1;
        
        double max_cos = 0.0;
        int tar = -1;

        vector<double> IDF;
        vector<double> TFq;

        for(auto &c : store){
            int Nx = 0;
            string target = c.first;
            TFq.push_back(store.count(target) ? double(store[target]) / query.size() : 0);

            for(int j = 1; R - j + 1 >= L; j++){
                int now = R - j + 1;
                if(stores[now].count(target)) Nx++;
            }
            IDF.push_back(log(double(len + 1) / (Nx + 1)) + 1);
        }

        for(int j = 1; R - j + 1 >= L; j++){
            vector<double> A(m);
            vector<double> B(m);
            int now = R - j + 1;
            double weight = double(K - j + 1) / K;
            vector<double> TFw;
            double sum = 0.0;
            for(auto &c : store){
                string target = c.first;
                TFw.push_back(stores[now].count(target) ? double(stores[now][target]) / files[now].size() : 0);
            }

            for(int i = 0; i < m; i++){
                A[i] = TFq[i] * IDF[i];
                B[i] = TFw[i] * IDF[i];
                // cout<<TFq[i]<<endl;
                // cout<<TFw[i]<<endl;
                // cout<<IDF[i]<<endl;
                sum += A[i] * B[i];
                // cout<<P<<endl;
                // cout<<i<<endl;
                //cout<<A[i]<<" "<<B[i]<<endl;
            }

            double now_cos = norm(A) * norm(B) == 0 ? 0 : sum  * weight/ (norm(A) * norm(B));
            if(now_cos >= 0.6 && now_cos >= max_cos){
                max_cos = now_cos;
                tar = now;
            }
        }
        if(!first) cout<<' ';
        else first = false;
        cout<<tar;
    }

    return 0;
}