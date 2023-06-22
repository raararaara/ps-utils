#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Matrix {
    int N{};
    vector<vector<T>> v;
    const T init;

    Matrix(int n, T init) :N(n), v(n, std::vector<T>(n, init)), init(init) {}

    T* operator[](int i) { return v[i].data(); }
    const T* operator[](int i) const { return v[i].data(); }

    Matrix operator * (const Matrix &rhs) const {
        Matrix ret(N, init);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    ret[i][j] += v[i][k] * rhs[k][j];
                }
            }
        }
        return ret;
    }

    Matrix operator *= (const Matrix &rhs) {
        Matrix ret(N, init);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    ret[i][j] += v[i][k] * rhs[k][j];
                }
            }
        }
        swap(v, ret.v);
        return *this;
    }

    static Matrix I(int n, const T& init) {
        Matrix ret(n, init);
        for (int i = 0; i < n; i++) { ret[i][i] = T(1); }
        return ret;
    }

    template<typename U>
    Matrix pow(U k) {
        if (!k) return I(N, init);
        if (k & 1) return pow(k - 1)*(*this);
        Matrix half = pow(k / 2);
        return half * half;
    }
};