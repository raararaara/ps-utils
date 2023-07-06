#pragma once
#include <bits/stdc++.h>
using namespace std;

/** Usage
* Hashing<p> strH = Hashing<p> (s, modSet);
**/

vector<long long> modSet= {1000000007, 1000000009, 998244353};
const long long p = 524287;
template<long long p>
struct Hashing {
    int N{}, msz{};
    vector<long long> mod;
    vector<vector<long long>> pw, h;
    Hashing() = default;
    Hashing(const string &str, vector<long long> &m): N(int(size(str))),msz(int(size(m))),mod(m){
        h = pw = vector<vector<long long>>(N, vector<long long>(msz));

        for(int j = 0; j < msz; j++) pw[0][j] = 1LL, h[0][j] = str[0];
        for(int i = 1; i < N; i++) {
            for (int j = 0; j < msz; j++) {
                h[i][j] = (h[i - 1][j] * p + str[i]) % mod[j];
                pw[i][j] = (pw[i - 1][j] * p) % mod[j];
                if(h[i][j] < 0) h[i][j] += mod[j];
                if(pw[i][j] < 0) pw[i][j] += mod[j];
            }
        }
    }

    vector<long long> get(int l, int r) {
        vector<long long> ret(msz);
        for(int j = 0; j < msz; j++) {
            ret[j] = h[r][j];
            if(l) ret[j] = (ret[j] - h[l-1][j] * pw[r-l+1][j]) % mod[j];
            if(ret[j] < 0) ret[j] += mod[j];
        }
        return ret;
    }
};