#include <bits/stdc++.h>
using namespace std;

static inline bool readInt(int &out) {
    int c = getchar_unlocked();
    while (c != EOF && c != '-' && (c < '0' || c > '9')) c = getchar_unlocked();
    if (c == EOF) return false;
    int sign = 1;
    if (c == '-') { sign = -1; c = getchar_unlocked(); }
    long long x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar_unlocked(); }
    out = (int)(x * sign);
    return true;
}

struct SegTree {
    int n;
    int k;
    vector<int> mn;
    vector<int> lazy;
    SegTree(int n_, int k_): n(n_), k(k_) {
        mn.assign(n_ * 4 + 5, k);
        lazy.assign(n_ * 4 + 5, 0);
    }
    inline void apply(int idx, int val) {
        mn[idx] += val;
        lazy[idx] += val;
    }
    inline void push(int idx) {
        if (lazy[idx] != 0) {
            int v = lazy[idx];
            apply(idx<<1, v);
            apply(idx<<1|1, v);
            lazy[idx] = 0;
        }
    }
    inline void pull(int idx) {
        mn[idx] = std::min(mn[idx<<1], mn[idx<<1|1]);
    }
    void range_add(int idx, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) { apply(idx, val); return; }
        push(idx);
        int mid = (l + r) >> 1;
        if (ql <= mid) range_add(idx<<1, l, mid, ql, qr, val);
        if (qr > mid) range_add(idx<<1|1, mid+1, r, ql, qr, val);
        pull(idx);
    }
    int range_min(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return mn[idx];
        push(idx);
        int mid = (l + r) >> 1;
        int res = INT_MAX;
        if (ql <= mid) res = min(res, range_min(idx<<1, l, mid, ql, qr));
        if (qr > mid) res = min(res, range_min(idx<<1|1, mid+1, r, ql, qr));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // Use fast C IO via readInt/putchar_unlocked
    int x, k, p;
    if (!readInt(x)) return 0;
    readInt(k); readInt(p);
    int segments = max(0, x - 1);
    if (segments == 0) {
        // No segments; only orders with v<=u would be trivial. Assume input has u<v; these cannot be satisfied.
        for (int i = 0; i < p; ++i) {
            int u,v,n; readInt(u); readInt(v); readInt(n);
            if (v <= u) {
                putchar_unlocked('T');
            } else {
                putchar_unlocked('N');
            }
            putchar_unlocked('\n');
        }
        return 0;
    }
    SegTree st(segments, k);
    for (int i = 0; i < p; ++i) {
        int u, v, n;
        readInt(u); readInt(v); readInt(n);
        if (v <= u) {
            putchar_unlocked('T');
            putchar_unlocked('\n');
            continue;
        }
        int l = u;
        int r = v - 1;
        if (l < 1) l = 1;
        if (r > segments) r = segments;
        if (l > r) {
            putchar_unlocked('T');
            putchar_unlocked('\n');
            continue;
        }
        int minAvail = st.range_min(1, 1, segments, l, r);
        if (minAvail >= n) {
            st.range_add(1, 1, segments, l, r, -n);
            putchar_unlocked('T');
        } else {
            putchar_unlocked('N');
        }
        putchar_unlocked('\n');
    }
    return 0;
}
