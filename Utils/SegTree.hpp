#pragma once
#include <bits/stdc++.h>
using namespace std;

/** Usage
* auto f = [](int a, int b) { return a + b; };
* SegTree<int, decltype(f)> seg(N, f, 0);
**/

template<typename T_Node, typename F>
struct SegTree {
    int N{}, base{};
    vector<T_Node> tree;
    const F f{};
    const T_Node I;

    SegTree(int n, F _f, const T_Node &I) : N(n), f(_f), I(I) {
        for (base = 1; base < N; base <<= 1);
        tree = vector<T_Node>(base<<1|1, I);
    }

    SegTree(vector<T_Node> &v, const T_Node &I) : N(int(size(v))), I(I) {
        for (base = 1; base < N; base <<= 1);
        tree = vector<T_Node>(base<<1|1, I);
        copy(all(v), tree.begin() + base);
        for(int i = base-1; ~i; --i) adjust(i);
    }

    T_Node get(int i) { return tree[i + base]; }

    T_Node top() { return tree[1]; }

    void upd(int i, T_Node v) {
        tree[i += base] = v;
        while (i >>= 1) adjust(i);
    }

    void adjust(int i) { tree[i] = f(tree[i << 1], tree[i << 1 | 1]); }

    T_Node qry(int l, int r) {
        T_Node retL = I, retR = I;
        for (l += base, r += base; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) retL = f(retL, tree[l++]);
            if (~r & 1) retR = f(tree[r--], retR);
        }
        return f(retL, retR);
    }
};
