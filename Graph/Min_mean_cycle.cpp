using ld = long double;
const ld inf = 1e100L;

struct edge {
    int from, to;
    ld weight;
};

// {has cycle, minimum mean}; karp, O(nm)
pair<bool, ld> min_mean_cycle(int n, const vector<edge> &edges) {
    vector<vector<ld>> dp(n + 1, vector<ld>(n, inf));
    ranges::fill(dp[0], 0); // super source
    for (int k = 1; k <= n; ++k)
        for (edge e : edges)
            if (dp[k - 1][e.from] != inf)
                dp[k][e.to] = min(dp[k][e.to], dp[k - 1][e.from] + e.weight);

    ld ans = inf;
    for (int v = 0; v < n; ++v) if (dp[n][v] != inf) {
        ld worst = -inf;
        for (int k = 0; k < n; ++k) if (dp[k][v] != inf)
            worst = max(worst, (dp[n][v] - dp[k][v]) / (n - k));
        ans = min(ans, worst);
    }
    return {ans != inf, ans};
}
