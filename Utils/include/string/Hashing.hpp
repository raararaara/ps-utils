#pragma once
#include <bits/stdc++.h>
using namespace std;

const int msz = 2, globalM = 1000001333;
array<long long, msz> mod= {1000000009, 1000000007};

template<int p>
struct Hashing {
    int n;
    string s;
    vector<vector<long long>> pw, h;
    Hashing(const string &str): n(int(size(str))), s(str) {
        h = pw = vector<vector<long long>>(n, vector<long long>(msz));

        for(int j = 0; j < msz; j++) pw[0][j] = 1LL, h[0][j] = str[0];
        for(int i = 1; i < n; i++) {
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

    bool equals(Hashing<p> &other) {
        return n == other.n && (get(0, n-1) == other.get(0, n-1));
    }

    bool contains(Hashing<p> &other) {
        int m = other.n;
        if(n < m) return false;
        for(int i = 0; i + m - 1 < n; i++) {
            if(get(i, i+m-1) == other.get(0, m-1)) return true;
        }
        return false;
    }
};

