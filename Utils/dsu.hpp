#pragma once
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(),(x).end()

template<int SZ> struct dsu {
    vector<int> par;
    dsu() {
        par = vector<int>(SZ+1);
        iota(all(par), 0);
    }

    int find(int u) {
        if(u == par[u]) return u;
        return par[u] = find(par[u]);
    }

    // mrg v to u
    void mrg(int u, int v) {
        u = find(u), v = find(v);
        if(u==v) return;
        par[v] = u;
    }
};