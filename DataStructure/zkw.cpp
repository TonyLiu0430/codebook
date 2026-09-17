// iterative segment tree: point add and range sum [l, r]
struct zkw_sum {
    int n = 1;
    vector<long long> t;
    zkw_sum(int size) {
        while (n < size) n *= 2;
        t.assign(2 * n, 0);
    }
    void add(int p, long long v) {
        for (t[p += n] += v, p /= 2; p; p /= 2)
            t[p] = t[p * 2] + t[p * 2 + 1];
    }
    long long sum(int l, int r) const {
        long long ans = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ans += t[l++];
            if (r & 1) ans += t[--r];
        }
        return ans;
    }
};
