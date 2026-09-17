// implicit/key treap primitives; node 0 means null
struct treap {
    struct node {
        int value = 0, priority = 0, size = 0, left = 0, right = 0;
    };
    struct split_result { int left, right; };
    vector<node> t{node{}};
    mt19937 rng{uint32_t(chrono::steady_clock::now().time_since_epoch().count())};

    int make_node(int value) {
        t.push_back({value, int(rng()), 1, 0, 0});
        return t.size() - 1;
    }
    int size(int u) const { return u ? t[u].size : 0; }
    void pull(int u) { t[u].size = 1 + size(t[u].left) + size(t[u].right); }

    split_result split_size(int u, int k) {
        if (!u) return {0, 0};
        if (size(t[u].left) >= k) {
            auto s = split_size(t[u].left, k);
            t[u].left = s.right;
            pull(u);
            return {s.left, u};
        }
        auto s = split_size(t[u].right, k - size(t[u].left) - 1);
        t[u].right = s.left;
        pull(u);
        return {u, s.right};
    }
    split_result split_value(int u, int value) {
        if (!u) return {0, 0};
        if (t[u].value <= value) {
            auto s = split_value(t[u].right, value);
            t[u].right = s.left;
            pull(u);
            return {u, s.right};
        }
        auto s = split_value(t[u].left, value);
        t[u].left = s.right;
        pull(u);
        return {s.left, u};
    }
    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        if (t[a].priority < t[b].priority) {
            t[a].right = merge(t[a].right, b);
            pull(a);
            return a;
        }
        t[b].left = merge(a, t[b].left);
        pull(b);
        return b;
    }
};
