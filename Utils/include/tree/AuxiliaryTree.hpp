#pragma once
#include <bits/stdc++.h>
#include "Hld.hpp"
using namespace std;

#define sz(x) int(size(x))
#define all(x) (x).begin(),(x).end()


template<typename T = int>
struct AuxiliaryTree : HLD<T> {
    using hld = HLD<T>;
    using hld::in;
    using hld::lca;

    vector<vector<int>> adj;

    explicit AuxiliaryTree(int n): hld(n), adj(n) {}

    void init(int rt = 0) {
        hld::build(rt);
    }

    void build(vector<int> &vec) {
        sort(all(vec), [&](int a, int b){
            return in[a] < in[b];
        });

        int n = sz(vec);
        for(int i = 1; i < n; i++) {
            vec.emplace_back(lca(vec[i-1], vec[i]));
        }

        sort(all(vec), [&](int a, int b){
            return in[a] < in[b];
        });
        vec.erase(unique(all(vec)), vec.end());
        for(auto &x: vec) {
            adj[x].clear();
        }

        n = sz(vec);
        for(int i = 1; i < n; i++) {
            int l = lca(vec[i-1], vec[i]);
            adj[l].emplace_back(vec[i]);
        }
    }
};