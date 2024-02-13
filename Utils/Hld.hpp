#pragma once
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(),(x).end()

// TODO: need explanation
struct HLD {
    vector<vector<int>> adj;
    vector<int> in, out, top, ch, par, inv;
    int dfn{};

    HLD(int n):adj(n), in(n, -1), out(n, -1), top(n), ch(n, 1), par(n, -1), inv(n) {}

    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void build(int rt = 0) {
        top[rt] = rt;
        par[rt] = -1;
        dfs_sz(rt);
        top[rt] = rt;
        dfs_hld(rt);
    }

    void dfs_sz(int cur) {
        if(~par[cur]) adj[cur].erase(find(all(adj[cur]), par[cur]));

        for(auto &nxt: adj[cur]) {
            par[nxt] = cur;
            dfs_sz(nxt);
            ch[cur] += ch[nxt];
            if(ch[nxt] > ch[adj[cur][0]]) {
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
        out[cur] = dfn;
    }

    int lca(int u, int v) {
        while(true) {
            if(in[u] > in[v]) swap(u, v);
            if(top[u] == top[v]) return u;
            v = par[top[v]];
        }
    }

    template<typename F>
    void vQry(int u, int v, const F& f) {
        while(true) {
            if(in[u] > in[v]) swap(u, v);
            f(max(in[top[v]], in[u]), in[v]);
            if(top[u] == top[v]) break;
            v = par[top[v]];
        }
    }

    template<typename F>
    void eQry(int u, int v, const F& f) {
        while(true){
            if(in[u]>in[v]) swap(u,v);
            if(top[u] != top[v]) {
                f(in[top[v]], in[v]);
                v = par[top[v]];
            } else {
                if(u != v) f(in[u] + 1, in[v]);
                break;
            }
        }
    }
};
