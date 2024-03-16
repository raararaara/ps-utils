#pragma once
#include <bits/stdc++.h>
#include "Tree.hpp"
using namespace std;

#define all(x) (x).begin(),(x).end()

// TODO: need explanation
template<typename T>
struct HLD: Tree<T> {
    using tree = Tree<T>;
    vector<vector<int>> adj;
    vector<int> in, out, top, inv;
    int dfn{};

    HLD(int n): Tree<T>(n), adj(n), in(n, -1), out(n, -1), top(n), inv(n) {}

    void build(int rt = 0) {
        top[rt] = rt;
        tree::par[rt] = -1;
        dfs_sz(rt);
        top[rt] = rt;
        dfs_hld(rt);
    }

    void dfs_sz(int cur) {
        if(~tree::par[cur]) adj[cur].erase(find(all(adj[cur]), tree::par[cur]));

        for(auto &nxt: adj[cur]) {
            tree::par[nxt] = cur;
            dfs_sz(nxt);
            tree::ch[cur] += tree::ch[nxt];
            if(tree::ch[nxt] > tree::ch[adj[cur][0]]) {
                swap(nxt, adj[cur][0]);
            }
        }
    }

    void dfs_hld(int cur) {
        in[cur] = dfn++;
        inv[in[cur]] = cur;
        for(auto &nxt: adj[cur]) {
            top[nxt] = (nxt == adj[cur][0] ? top[cur] : nxt);
            dfs_hld(nxt);
        }
        out[cur] = dfn - 1;
    }

    int lca(int u, int v) {
        while(true) {
            if(in[u] > in[v]) swap(u, v);
            if(top[u] == top[v]) return u;
            v = tree::par[top[v]];
        }
    }

    // NOTE: unsafe to use this method
    template<typename F>
    void qry_vertex(int u, int v, const F& f) {
        while(true) {
            if(in[u] > in[v]) swap(u, v);
            f(max(in[top[v]], in[u]), in[v]);
            if(top[u] == top[v]) break;
            v = tree::par[top[v]];
        }
    }

    template<typename F>
    void qry_edge(int u, int v, const F& f) {
        while(true){
            if(in[u]>in[v]) swap(u,v);
            if(top[u] != top[v]) {
                f(in[top[v]], in[v]);
                v = tree::par[top[v]];
            } else {
                if(u != v) f(in[u] + 1, in[v]);
                break;
            }
        }
    }
};
