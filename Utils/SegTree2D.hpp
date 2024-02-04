#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T_Node, typename F>
struct SegTree2D {
    int rBase{}, cBase{};
    vector<T_Node> tree;
    const F f{};
    const T_Node I;

    SegTree2D(int r, int c, F _f, const T_Node &I) : f(_f), I(I) {
        rBase = cBase = 1;
        while(rBase < r) rBase <<= 1;
        while(cBase < c) cBase <<= 1;
        tree.resize((rBase << 1) * (cBase << 1), I);
    }

    int id(int r, int c) { return (r<<1) * cBase + c; }

    T_Node get(int r, int c) { return tree[id(r + rBase, c + cBase)]; }

    void upd(int r, int c, T_Node v) {
        r += rBase, c += cBase;
        tree[id(r, c)] = v;
        for(int i = r >> 1; i; i >>= 1) {
            tree[id(i,c)] = f(tree[id(i<<1, c)], tree[id(i<<1|1, c)]);
        }
        for(;r; r >>= 1) {
            for(int j = c>>1; j; j >>= 1) {
                tree[id(r,j)] = f(tree[id(r, j<<1)], tree[id(r, j<<1|1)]);
            }
        }
    }

    T_Node qry1D(int r, int c1, int c2) {
        T_Node ret = I;
        for (c1 += cBase, c2 += cBase; c1 <= c2; c1 >>= 1, c2 >>= 1) {
            if (c1 & 1) ret = f(ret, tree[id(r, c1++)]);
            if (~c2 & 1) ret = f(tree[id(r, c2--)], ret);
        }
        return ret;
    }

    T_Node qry(int r1, int r2, int c1, int c2) {
        T_Node ret = I;
        for(r1 += rBase, r2 += rBase; r1 <= r2; r1 >>= 1, r2 >>= 1) {
            if(r1 & 1) ret = f(ret, qry1D(r1++, c1, c2));
            if(~r2 & 1) ret = f(ret, qry1D(r2--, c1, c2));
        }

        return ret;
    }
};
