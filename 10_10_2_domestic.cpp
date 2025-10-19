#include <bits/stdc++.h>
#include <sstream>
using namespace std;

double eps;

bool isNeibour(vector<double>& a, vector<double>& b){
    double square = 0;
    for(int i = 0; i < a.size(); i++){
        square += (a[i] - b[i]) * (a[i] - b[i]);
    }
    double distance = sqrt(square);
    return distance < eps ? true : false;
}

int main(){
    int min_samples, x;
    string line;
    getline(cin, line);
    stringstream ss(line);
    string token;
    ss>>eps>>min_samples>>x;
    vector<vector<double>> points;
    for(int i = 0; i < x; i++){
        vector<double> point;
        getline(cin, line);
        stringstream ss(line);
        double ordination;
        while(ss>>ordination){
            point.push_back(ordination);
        }
        points.push_back(point);
    }
    int num = points.size();

    int count = 0;

    vector<int> counted(num, 0);
    vector<int> nums;

    for(int i = 0; i < num; i++){
        vector<int> visited = counted;
        if(visited[i] == 0){
            bool cu = false;
            queue<int> q;
            q.push(i);
            while(!q.empty()){
                int now = q.front();
                q.pop();
                int sum = 0;
                for(int j = 0; j < num; j++){
                    if(j == now) continue;
                    if(isNeibour(points[now], points[j])){
                        sum++;
                    }
                }
                if(sum > min_samples){
                    if(cu == false) count++;
                    cu = true;
                    for(int j = 0; j < num; j++){
                        if(visited[j] != 0) continue;
                        if(isNeibour(points[now], points[j])){
                            q.push(j);
                            visited[j] = count;
                            visited[i] = count;
                        }
                    }
                }
            }
            if(cu){
                counted = visited;
            }
        }
    }
    int dis = 0;
    for(int i = 0; i < num; i++){
        if(counted[i] == 0) dis++;
    }
    cout<<count<<" "<<dis;
    return 0;
}