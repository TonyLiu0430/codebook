// public indices are 0-based
struct bit {
    vector<long long> t;
    bit(int n) : t(n + 1) {}

    void add(int p, long long x) {
        for (++p; p < (int)t.size(); p += p & -p) t[p] += x;
    }
    long long prefix(int r) const { // [0, r]
        long long ans = 0;
        for (++r; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }
    long long sum(int l, int r) const { // [l, r]
        return l > r ? 0 : prefix(r) - (l ? prefix(l - 1) : 0);
    }
};
