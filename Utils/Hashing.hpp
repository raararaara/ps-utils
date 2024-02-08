#pragma once
#include <bits/stdc++.h>
using namespace std;

const int msz = 2, globalM = 1000001333;
array<long long, msz> mod= {1000000009, 1000000007};

template<int p>
struct Hashing {
    int N;
    vector<vector<long long>> pw, h;
    Hashing() = default;
    Hashing(const string &str): N(int(size(str))) {
        h = pw = vector<vector<long long>>(N, vector<long long>(msz));

        for(int j = 0; j < msz; j++) pw[0][j] = 1LL, h[0][j] = str[0];
        for(int i = 1; i < N; i++) {
            for (int j = 0; j < msz; j++) {
                h[i][j] = (h[i-1][j] * p + str[i]) % mod[j];
                pw[i][j] = (pw[i-1][j] * p) % mod[j];
            }
        }
    }

    long long get(int l, int r) {
        long long ret = 1;
        for(int j = 0; j < msz; j++) {
            long long x = h[r][j];
            if(l) x = (x - h[l-1][j] * pw[r-l+1][j]) % mod[j];
            if(x < 0) x += mod[j];

            ret = (ret * globalM) + x;
        }
        return ret;
    }
};
