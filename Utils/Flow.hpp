#pragma once
#include <bits/stdc++.h>
using namespace std;

#define pb(x) emplace_back(x)

// copy&paste from here
// example: http://boj.kr/4af267966ea741919ddf9bfe7180f0e2
int N, M, S, T;

const int mxn = 100, INF = 1e9+7, mxe = 500050;
// mxe : maximum connection * 2

int E, to[mxe], cap[mxe], tot;
vector<int> adj[mxn];
int dist[mxn], cnt[mxn];

void addE(int u, int v, int c) {
    adj[u].pb(E); to[E] = v; cap[E++] = c;
    adj[v].pb(E); to[E] = u; cap[E++] = c;
}


void bfs() {
    fill(dist, dist + N+1, N);
    queue<int> q;
    dist[T] = 0; q.emplace(T);
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int &e: adj[cur]) {
            int prv = to[e], f = cap[e^1];
            if(f && dist[prv] == N) {
                dist[prv] = dist[cur] + 1;
                q.emplace(prv);
            }
        }
    }
    memset(cnt, 0, sizeof cnt);
    for(int i = 1; i <= N; i++) cnt[dist[i]]++;
}

vector<int> pathE;
int dfs(int cur) {
    if(cur == T) return 1;
    for(int &e: adj[cur]) {
        int nxt = to[e], f = cap[e];
        if(!f || dist[nxt] + 1 != dist[cur]) continue;
        pathE.pb(e);

        int fl = dfs(nxt);
        if(fl) return fl;
        pathE.pop_back();
    }

    int tmp = dist[cur];
    dist[cur] = N;
    for(int &e: adj[cur]) {
        int nxt = to[e], f = cap[e];
        if(!f) continue;
        dist[cur] = min(dist[cur], dist[nxt] + 1);
    }
    cnt[dist[cur]]++;
    if(!--cnt[tmp]) return -1;
    return 0;
}

int flow() {
    int ret = 0;
    bfs();
    while(dist[S] < N) {
        pathE.clear();
        int x = dfs(S);
        if(x < 0) break;
        if(!x) continue;
        int f = INF;
        for(int &e: pathE) f = min(f, cap[e]);
        for(int &e: pathE) cap[e] -= f, cap[e^1] += f;
        ret+=f;
    }

    return ret;
}

bitset<mxn> vis;
void getAB(int st) {
    queue<int> q;
    vis[st] = true;
    q.emplace(st);

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int &e: adj[cur]) {
            int nxt = to[e], f = cap[e];
            if(!vis[nxt] && f) {
                vis[nxt] = true;
                q.emplace(nxt);
            }
        }
    }
    for(int i = 0; i < N; i++) if(vis[i]) cout << i+1 << ' ';
    cout << '\n';
    for(int i = 0; i < N; i++) if(!vis[i]) cout << i+1 << ' ';
}