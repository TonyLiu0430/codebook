using ld = long double;

ld int_power(ld x, int p) {
    ld ans = 1;
    for (; p; p /= 2, x *= x) if (p & 1) ans *= x;
    return ans;
}

// original line-breaking transition; returns dp[n]
ld line_break_dp(const vector<int> &length, int limit, int power) {
    struct interval { int l, r, pos; };
    int n = length.size();
    vector<long long> prefix(n + 1);
    vector<ld> dp(n + 1);
    for (int i = 1; i <= n; ++i) prefix[i] = prefix[i - 1] + length[i - 1];
    auto cost = [&](int i, int j) {
        ld extra = fabsl(prefix[i] - prefix[j] + i - j - 1 - limit);
        return dp[j] + int_power(extra, power);
    };

    vector<interval> stack(n + 2);
    int top = 0, bottom = 0;
    stack[0] = {1, n + 1, 0};
    for (int i = 1; i <= n; ++i) {
        while (i >= stack[bottom].r) ++bottom;
        dp[i] = cost(i, stack[bottom].pos);
        while (top > bottom && i < stack[top].l &&
               cost(stack[top].l, i) < cost(stack[top].l, stack[top].pos)) {
            stack[top - 1].r = stack[top].r;
            --top;
        }
        int l = stack[top].l, r = stack[top].r, old = stack[top].pos;
        while (l < r) {
            int m = (l + r) / 2;
            if (cost(m, i) < cost(m, old)) r = m;
            else l = m + 1;
        }
        if (l < stack[top].r) {
            int old_r = stack[top].r;
            stack[top].r = l;
            stack[++top] = {l, old_r, i};
        }
    }
    return dp[n];
}
