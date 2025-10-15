#include <bits/stdc++.h>
using namespace std;

struct LstmParams {
    std::vector<std::vector<double>> wg = {
        {0.009763f, 0.043038f, 0.020553f, 0.008977f, -0.015209f, 0.000179f, -0.012636f, 0.017535f, -0.022032f, 0.06664f, 0.06077f, 0.02607f},
        {0.013609f, 0.095119f, -0.085793f, -0.095274f, -0.099966f, 0.086524f, 0.056641f, 0.074002f, 0.06774f, -0.00704f, 0.00686f, -0.01013f},
        {-0.076345f, 0.027984f, -0.071329f, 0.088934f, 0.00437f, -0.017065f, -0.047089f, 0.046647f, -0.06871f, 0.00387f, -0.00661f, -0.01133f},
        {0.022419f, 0.023837f, 0.08375f, 0.036964f, -0.028098f, -0.012594f, 0.039626f, -0.03785f, 0.03383f, 0.00188f, -0.00723f, -0.06378f},
        {-0.036914f, -0.027258f, 0.014093f, -0.01228f, 0.007675f, -0.078691f, -0.058225f, -0.05922f, -0.04942f, -0.06378f, -0.01133f, 0.00689f}
    };

    std::vector<std::vector<double>> wi = {
        {-0.012801f, -0.094815f, 0.009932f, -0.012938f, -0.015208f, -0.03393f, -0.06907f, 0.02384f, -0.04069f, -0.04695f, 0.04227f, 0.00689f},
        {-0.073084f, 0.002716f, -0.063112f, 0.057087f, 0.017075f, -0.001143f, 0.06291f, -0.06470f, 0.00196f, -0.06943f, -0.04476f, -0.00694f},
        {-0.074568f, 0.019349f, -0.054798f, -0.076611f, -0.053938f, -0.030035f, -0.00644f, -0.06951f, 0.02981f, -0.03384f, 0.00647f, -0.02581f},
        {0.058727f, 0.016001f, -0.06754f, 0.04015f, 0.09291f, 2e-06f, 0.077904f, -0.031577f, 0.01303f, -0.01410f, -0.01398f, 0.05501f},
        {0.007121f, 0.090749f, 0.005842f, -0.053581f, -0.025732f, 0.07017f, -0.018745f, -0.09456f, -0.05945f, -0.06571f, 0.06871f, 0.00411f}
    };

    std::vector<std::vector<double>> wf = {
        {-0.084738f, 0.055984f, -0.012318f, 0.044693f, 0.065598f, 0.007089f, 0.000224f, -0.06559f, -0.04612f, -7.3e-05f, 0.03686f, 0.06116f},
        {-0.023812f, -0.086313f, -0.042371f, 0.081919f, -0.057323f, -0.009575f, 0.086241f, -0.05902f, 0.03011f, 0.00626f, -0.05909f, 0.00688f},
        {0.081826f, -0.073366f, 0.004863f, 0.050082f, 0.033803f, -0.005449f, -0.05630f, -0.00347f, -0.02532f, -0.0456f, -0.02682f, 0.03758f},
        {0.05373f, -0.037201f, 0.014525f, -0.04479f, -0.009431f, -0.029404f, 0.03148f, -0.02329f, -0.03618f, 0.03586f, -0.01707f, 0.01834f},
        {-0.06391f, 0.048224f, -0.015252f, -0.014709f, 0.028876f, 0.004581f, -0.017023f, -0.09715f, -0.03168f, 0.04157f, 0.04680f, 0.05221f}
    };

    std::vector<std::vector<double>> wo = {
        {0.022434f, -0.066186f, -0.012788f, 0.053852f, -0.040935f, -0.070167f, -0.05504f, -0.01525f, -0.05224f, -0.05249f, 0.03916f, -0.05965f},
        {-0.083761f, 0.03392f, 0.024249f, -0.045149f, -0.006756f, -0.076326f, -0.085208f, 0.08015f, 0.05878f, 0.06814f, 0.05341f, 0.06931f},
        {0.015455f, 0.062753f, -0.015736f, -0.09451f, -0.009173f, -0.079835f, 0.063444f, 0.039546f, 0.03367f, -0.05155f, 0.09695f, 0.07272f},
        {0.023083f, -0.002993f, -0.015995f, 0.04557f, -0.035437f, -0.019891f, -0.039207f, 0.08944f, 0.08376f, 0.06708f, -0.09135f, 0.06871f},
        {0.090088f, 0.061318f, -0.003744f, 0.093352f, -0.016804f, -0.036232f, -0.096711f, -0.05294f, -0.06852f, -0.01468f, -0.03823f, -0.06719f}
    };

    std::vector<double> bg = {-0.017119f, -0.010762f, -0.01027f, -0.075269f, -0.065529f};
    std::vector<double> bi = {0.075116f, 0.059407f, 0.049271f, -0.074094f, 0.054991f};
    std::vector<double> bf = {0.018351f, -0.01307f, -0.014564f, 0.009966f, 0.066618f};
    std::vector<double> bo = {-0.054807f, -0.077083f, -0.014593f, 0.047107f, 0.007309f};
};

vector<double> dot_product(vector<vector<double>>& matrix, vector<double>& vec){
    vector<double> result(matrix.size(), 0.0);
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < vec.size(); j++){
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

vector<double> add(const vector<double>& v1, const vector<double>& v2){
    vector<double> result = v1;
    for(int i = 0; i < v1.size(); i++){
        result[i] += v2[i];
    }
    return result;
}

vector<double> multi(vector<double>& v1, vector<double>& v2){
    vector<double> result = v1;
    for(int i = 0; i < v1.size(); i++){
        result[i] *= v2[i];
    }
    return result;
}

void apply_sigmoid(vector<double>& vec){
    for(double& val : vec){
        val = 1.0 / (1.0 + exp(-val));
    }
}

void apply_tanh(vector<double>& vec){
    for(double& val : vec){
        val = tanh(val);
    }
}

double round3(double x){
    return round(x * 1000) / 1000;
}

int main(){
    LstmParams params;
    string line;
    getline(cin, line);
    stringstream ss(line);
    int row, col;
    ss>>row>>col;
    vector<vector<double>> data(row, vector<double> (col));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            ss>>data[i][j];
        }
    }
    int memory_length = 5;
    vector<double> h_pre(memory_length, 0.0);
    vector<double> s_pre(memory_length, 0.0);

    vector<vector<double>> h_list;

    for(auto& x : data){
        vector<double> xc = x;
        for(double c : h_pre){
            xc.push_back(c);
        }

        vector<double> g = add(dot_product(params.wg, xc), params.bg);
        apply_tanh(g);

        vector<double> o = add(dot_product(params.wo, xc), params.bo);
        apply_sigmoid(o);

        vector<double> i = add(dot_product(params.wi, xc), params.bi);
        apply_sigmoid(i);

        vector<double> f = add(dot_product(params.wf, xc), params.bf);
        apply_sigmoid(f);

        vector<double> s = add(multi(f, s_pre), multi(i, g));

        vector<double> s_tanh = s;
        apply_tanh(s_tanh);
        vector<double> h = multi(s_tanh, o);

        h_list.push_back(h);
        h_pre = h;
        s_pre = s;
    }

    for(int i = 0; i < row; i++){
        if(i) cout<<" ";
        cout<<round3(h_list[i][0]);
        //cout<<fixed<<setprecision(3)<<h_list[i][0];
    }

    return 0;
}