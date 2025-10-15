#include <bits/stdc++.h>
using namespace std;

double round4(double x){
    return round(x * 10000) / 10000;
}

int main(){
    int b,d,r;
    cin>>b>>d>>r;
    vector<vector<double>> x(b, vector<double>(d));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            cin>>x[i][j];
        }
    }

    vector<vector<double>> wq(d, vector<double>(d));
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            cin>>wq[i][j];
        }
    } 
    vector<vector<double>> wk(d, vector<double>(d));
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            cin>>wk[i][j];
        }
    } 
    vector<vector<double>> wv(d, vector<double>(d));
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            cin>>wv[i][j];
        }
    } 

    if(r > 0){
        vector<vector<double>> A(r, vector<double> (d));
        for(int i = 0; i < r; i++){
            for(int j = 0; j < d; j++){
                cin>>A[i][j];
            }
        } 
        vector<vector<double>> B(d, vector<double> (r));
        for(int i = 0; i < d; i++){
            for(int j = 0; j < r; j++){
                cin>>B[i][j];
            }
        } 
        vector<vector<double>> AB(d, vector<double>(d,0.0));
        for(int i = 0; i < d; i++){
            for(int j = 0; j < d; j++){
                for(int k = 0; k < r; k++){
                    AB[i][j] += B[i][k] * A[k][j];
                }
                wq[i][j] += AB[i][j];
            }
        } 
    }

    vector<vector<double>> Q(b, vector<double> (d,0.0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < d; k++){
                Q[i][j] += x[i][k] * wq[j][k];
            }
        }
    } 
    vector<vector<double>> K(b, vector<double> (d,0.0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < d; k++){
                K[i][j] += x[i][k] * wk[j][k];
            }
        }
    } 
    vector<vector<double>> V(b, vector<double> (d,0.0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < d; k++){
                V[i][j] += x[i][k] * wv[j][k];
            }
        }
    } 

    vector<vector<double>> inside(b, vector<double> (b,0.0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < b; j++){
            for(int k = 0; k < d; k++){
                inside[i][j] += Q[i][k] * K[j][k];
            }
            inside[i][j] /= sqrt(d);
        }
    } 

    for(int i = 0; i < b; i++){
        double m = inside[i][0];
        for(int j = 0; j < b; j++){
            m = max(m, inside[i][j]);
        }
        double sum = 0.0;
        for(int j = 0; j < b; j++){
            inside[i][j] = exp(inside[i][j] - m);
            sum += inside[i][j];
        }
        for(int j = 0; j < b; j++){
            inside[i][j] /= sum;
        }
    }    

    vector<vector<double>> output(b, vector<double> (d,0.0));
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            for(int k = 0; k < b; k++){
                output[i][j] += inside[i][k] * V[k][j];
            }
        }
    }  

    bool first = true;
    for(int i = 0; i < b; i++){
        for(int j = 0; j < d; j++){
            if(first) first = false;
            else {
                cout<<' ';
            }
            cout<<fixed<<setprecision(4)<<round4(output[i][j]);
        }
    }   
    return 0;
}