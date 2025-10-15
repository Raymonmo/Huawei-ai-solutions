#include <bits/stdc++.h>
using namespace std;

static vector<long long> parseLineLL(const string &s) {
    vector<long long> v;
    string cur;
    for (size_t i = 0; i <= s.size(); ++i) {
        if (i == s.size() || isspace(static_cast<unsigned char>(s[i]))) {
            if (!cur.empty()) {
                v.push_back(stoll(cur));
                cur.clear();
            }
        } else {
            cur.push_back(s[i]);
        }
    }
    return v;
}
long long batch_size;
long long in_channels;
long long height;
long long width;
long long out_channels;
long long k_channels;
long long kernel_h;
long long kernel_w;
long long group;
long long Ho;
long long Wo;

long long idx_in(long long n, long long c, long long h, long long w){
    return n * (in_channels * height * width) + c * (height * width) + h * width + w;
}

long long idx_ker(long long oc, long long kc, long long kh, long long kw){
    return oc * (k_channels * kernel_h * kernel_w) + kc * (kernel_h * kernel_w) 
    + kh * kernel_w + kw;
}

long long idx_out(long long n, long long oc, long long h, long long w){
    return n * (out_channels * Ho * Wo) + oc * (Ho * Wo) + h * Wo + w;
}

int main(){
    string line1, line2, line3, line4, line5;
    if (!std::getline(cin, line1)) { cout << "-1\n-1\n"; return 0; }
    if (!std::getline(cin, line2)) { cout << "-1\n-1\n"; return 0; }
    if (!std::getline(cin, line3)) { cout << "-1\n-1\n"; return 0; }
    if (!std::getline(cin, line4)) { cout << "-1\n-1\n"; return 0; }
    if (!std::getline(cin, line5)) { cout << "-1\n-1\n"; return 0; }

    // 解析
    vector<long long> in_data_ll = parseLineLL(line1);
    vector<long long> in_shape_ll = parseLineLL(line2);
    vector<long long> ker_data_ll = parseLineLL(line3);
    vector<long long> ker_shape_ll = parseLineLL(line4);
    vector<long long> groups_ll = parseLineLL(line5);
    
    if (in_shape_ll.size() != 4 || ker_shape_ll.size() != 4 || groups_ll.size() != 1) {
        cout << "-1\n-1\n";
        return 0;
    }

    batch_size = in_shape_ll[0];
    in_channels = in_shape_ll[1];
    height = in_shape_ll[2];
    width = in_shape_ll[3];

    out_channels = ker_shape_ll[0];
    k_channels = ker_shape_ll[1];
    kernel_h = ker_shape_ll[2];
    kernel_w = ker_shape_ll[3];

    group = groups_ll[0];

    Ho = height - kernel_h + 1;
    Wo = width - kernel_w + 1;

    if(Ho <= 0 || Wo <= 0){
        cout<< "-1\n -1\n";
        return 0;
    }

    long long OCg = out_channels / group;
    long long KCg = k_channels;

    vector<long long> y(batch_size * out_channels * Ho * Wo, 0);

    for(long long n = 0; n < batch_size; n++){
        for(long long g = 0; g < group; g++){
            for(long long ocg = 0; ocg < OCg; ocg++){
                long long oc_idx = g * OCg + ocg;
                for(long long oh = 0; oh < Ho; oh++){
                    for(long long ow = 0; ow < Wo; ow++){
                        long long acc = 0;
                        for(long long kc = 0; kc < KCg; kc++){
                            long long ic = g * KCg + kc;
                            for(long long kh = 0; kh < kernel_h; kh++){
                                for(long long kw = 0; kw < kernel_w; kw++){
                                    long long ih = oh + kh;
                                    long long iw = ow + kw;
                                    long long xv = in_data_ll[idx_in(n, ic, ih, iw)];
                                    long long kv = ker_data_ll[idx_ker(oc_idx, kc, kh, kw)];
                                    acc += xv * kv;
                                }
                            }
                        }
                        y[idx_out(n, oc_idx, oh, ow)] = acc;
                    }
                }
            }
        }
    }

    for(long long i = 0; i < y.size(); i++){
        if(i) cout<<' ';
        cout<<y[i];
    }
    cout<<'\n';
    cout<<batch_size<<' '<<out_channels<<' '<<Ho<<' '<<Wo<<endl;
    return 0;
}