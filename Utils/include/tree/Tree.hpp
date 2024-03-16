#pragma once
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(),(x).end()

template<typename T>
struct Tree {
    struct EDG {
        int u, v;
        T w;
        EDG() = default;
        EDG(int u, int v, T w): u(u), v(v), w(w){}
    };

    vector<vector<int>> adj;
    vector<int> ch, par;
    vector<EDG> eList;
    vector<T> weight;

    Tree(int n): adj(n), ch(n, 1), par(n, -1), weight(n) {}

    void build(int rt = 0) {
        make_tree(rt);

        // adjust (u,v,w) as (u,par[u],w)
        for(auto &[u, v, w]: eList) {
            if(u == par[v]) swap(u, v);
            weight[u] = w;
        }
    }

    void make_tree(int cur) {
        if(~par[cur]) adj[cur].erase(find(all(adj[cur]), par[cur]));

        for(auto &nxt: adj[cur]) {
            par[nxt] = cur;
            make_tree(nxt);
            ch[cur] += ch[nxt];
            if(ch[nxt] > ch[adj[cur][0]]) {
                swap(nxt, adj[cur][0]);
            }
        }
    }

    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void add_edge(int u, int v, T w) {
        eList.emplace_back(u, v, w);
    }

    // diameter
    T get_diameter(int rt = 0) {
        int x;  // end point of diameter
        T ret = 0;
        auto dfs = [&](const auto &self, int cur, int prv, T dist) -> T {
            if(ret < dist) {
                ret = dist; x = cur;
            }
            for(auto &nxt: adj[cur]) {
                if(nxt != prv) {
                    self(nxt, cur, dist + weight[nxt]);
                }
            }
        };

        dfs(rt, -1, 0); ret = 0;
        dfs(x, -1, 0);

        return ret;
    }
};
