// persistent segment tree on [0, n): point add, range sum
// every add returns a new root; root 0 is the empty tree
// reserve about (updates * (log n + 2)) nodes if memory is tight
using ll = long long;

struct persistent_seg {
    struct node { int l = 0, r = 0; ll sum = 0; };
    int n;
    vector<node> t{node{}};

    persistent_seg(int n) : n(n) {}
    int add(int u, int l, int r, int p, ll v) {
        int id = t.size();
        t.push_back(t[u]);
        t[id].sum += v;
        if (l < r) {
            // C++17: the right side of = runs first
            int m = (l + r) / 2;
            if (p <= m) t[id].l = add(t[id].l, l, m, p, v);
            else t[id].r = add(t[id].r, m + 1, r, p, v);
        }
        return id;
    }
    int add(int root, int p, ll v) {
        return add(root, 0, n - 1, p, v);
    }
    ll sum(int u, int l, int r, int ql, int qr) {
        if (!u || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[u].sum;
        int m = (l + r) / 2;
        return sum(t[u].l, l, m, ql, qr) +
               sum(t[u].r, m + 1, r, ql, qr);
    }
    ll sum(int root, int ql, int qr) {
        return sum(root, 0, n - 1, ql, qr);
    }
    // k-th (0-based) smallest position of version b minus version a
    // e.g. root[i] = add(root[i-1], a[i], 1); kth(root[l-1], root[r], k)
    int kth(int a, int b, ll k) {
        int l = 0, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            ll left = t[t[b].l].sum - t[t[a].l].sum;
            if (k < left) a = t[a].l, b = t[b].l, r = m;
            else {
                k -= left;
                a = t[a].r, b = t[b].r, l = m + 1;
            }
        }
        return l;
    }
};
