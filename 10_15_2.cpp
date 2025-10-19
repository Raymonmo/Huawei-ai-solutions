#include <bits/stdc++.h>
#include <queue>
using namespace std;

double attention(vector<double>& vec1, vector<double>& vec2){
    int n = vec1.size();
    double sum = 0.0;
    for(int i = 0; i < n; i++){
        sum += vec1[i] * vec2[i];
    }
    return sum / sqrt(n) * sum / sqrt(n);
}

int main(){
    int n, d;
    cin>>n>>d;

    vector<vector<double>> data(n, vector<double> (d));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < d; j++){
            cin>>data[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        double sum = 0.0;
        for(int j = 0; j < d; j++){
            sum += data[i][j] * data[i][j];
        }
        sum = sqrt(sum / d);
        for(int j = 0; j < d; j++){
            data[i][j] /= sum;
        }        
    }

    vector<int> c(n);
    for(int i = 0; i < n; i++){
        cin>>c[i];
    }
    double s = 0.0;
    vector<vector<int>> M(n, vector<int> (n,0));
    for(int j = 1; j < n; j++){
        vector<double> scores;
        for(int i = 0; i < j; i++){
            double now_a = attention(data[i],data[j]);
            scores.push_back(now_a);
        }
        sort(scores.begin(), scores.end(), greater<double>());
        int now_c = c[j];
        for(int i = 0; i < now_c; i++){
            s += scores[i];
        }
    }

    cout<<(int)round(100 * s);

    return 0;
}