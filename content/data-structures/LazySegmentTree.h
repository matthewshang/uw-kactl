/**
 * Author: Evirir
 * Date: 2024-09-02
 * License: CC0
 * Source: me
 * Description: Segment tree
 * Time: O(\log N).
 * Status: stress-tested a bit
 */
#pragma once

class LazySegmentTree {
private:
    static constexpr ll kDef = 0;
    static constexpr ll kDum = 0;
    static constexpr ll kDefLazy = 0;

    int size_;
    vector<ll> v, lazy;

    void update(int s, int e, ll val, int k, int l, int r) {
        if (r < s || e < l) return;
        if (s <= l && r <= e) {
            lazy[k] += val;
            apply(k, l, r, val);
            return;
        }
        push(k, l, r);
        update(s, e, val, k * 2, l, (l + r) >> 1);
        update(s, e, val, k * 2 + 1, ((l + r) >> 1) + 1, r);
        v[k] = merge(v[k * 2], v[k * 2 + 1]);
    }

    ll query(int s, int e, int k, int l, int r) {
        if (r < s || e < l) return kDum;
        if (s <= l && r <= e) return v[k];
        push(k, l, r);
        ll lc = query(s, e, k * 2, l, (l + r) >> 1);
        ll rc = query(s, e, k * 2 + 1, ((l + r) >> 1) + 1, r);
        return merge(lc, rc);
    }

public:
    LazySegmentTree() : v{}, lazy{} {}
    LazySegmentTree(int n) {
        for (size_ = 1; size_ < n;) size_ <<= 1;
        v.resize(size_ * 4, kDef);
        lazy.resize(size_ * 4, kDefLazy);
    }
    inline void push(int k, int l, int r) {
        if (lazy[k] == kDefLazy) return;
        if (l != r) {
            int mid = (l + r) >> 1;
            lazy[k * 2] += lazy[k];
            apply(k * 2, l, mid, lazy[k]);
            lazy[k * 2 + 1] += lazy[k];
            apply(k * 2 + 1, mid + 1, r, lazy[k]);
        }
        lazy[k] = kDefLazy;
    }
    void apply(int k, int l, int r, ll val) {
        v[k] += (r - l + 1) * val;  // remember to consider the range!
    }
    inline ll merge(ll x, ll y) {
        return x + y;
    }
    inline void update(int l, int r, ll val) {
        update(l, r, val, 1, 0, size_ - 1);
    }
    inline ll query(int l, int r) {
        return query(l, r, 1, 0, size_ - 1);
    }
};
