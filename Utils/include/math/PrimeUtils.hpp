#pragma once
#include <bits/stdc++.h>
using namespace std;
using lint = long long;

template<typename K, typename V, int SZ>
struct PrimeUtils {
    const lint LNF = 1e16;
    vector<int> spf, pList;
    PrimeUtils() {
        spf = vector<int>(SZ);
        sieve();
    }

    void sieve() {
        for (int i = 2; i < SZ; i++) {
            if(!spf[i]) {
                pList.emplace_back(i);
                spf[i] = i;
            }
            for (int j = 0; i * pList[j] < SZ; j++) {
                spf[i * pList[j]] = pList[j];
                if (i % pList[j] == 0) break;
            }
        }
    }

    bool IsPrime(K n) {
        if(n < SZ) return spf[n] == n;
        else if(n < LNF) return isPrimeSqrtN(n);
    }
    bool isPrimeSqrtN(K n) {
        if (n == 2 || n == 3) return true;
        if (n <= 1 || n % 2 == 0 || n % 3 == 0) return false;

        for (K i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    vector<pair<K,V>> Factorize(K x) {
        if(x < SZ) return factorizeSmall(x);
        else if(x < LNF) factorizeSqrtN(x);
    }
    vector<pair<K,V>> factorizeSmall(K n) {
        vector<pair<K,V>> ret;
        while(n != 1) {
            if(ret.empty() || ret.back().first != spf[n]) ret.push_back({spf[n], 0});
            ret.back().second++;
            n /= spf[n];
        }
        return ret;
    }
    vector<pair<K,V>> factorizeSqrtN(K n) {
        vector<pair<K,V>> ret;

        V cnt2 = 0;
        while(n % 2 == 0) {
            cnt2++;
            n >>= 1;
        }
        if(cnt2) ret.push_back({2, cnt2});
        for(K i = 3; i * i <= n; i += 2) {
            V cnt = 0;
            while(n % i == 0) {
                cnt++;
                n /= i;
            }
            if(cnt) ret.push_back({i, cnt});
        }
        if(n > 1) ret.push_back({n, 1});
        return ret;
    }
};