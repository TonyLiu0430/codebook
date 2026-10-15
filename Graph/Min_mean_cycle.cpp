// 最小平均權環（環上邊權平均最小）：Karp 演算法 O(nm)。
using ld = long double;
const ld inf = 1e100L;

struct edge {
    int from, to;
    ld weight;
};

// {has cycle, minimum mean}; karp, O(nm)
pair<bool, ld> min_mean_cycle(int n,
                              const vector<edge> &edges) {
    vector<vector<ld>> dp(n + 1, vector<ld>(n, inf));
    ranges::fill(dp[0], 0); // super source
    for (int k = 1; k <= n; ++k)
        for (edge e : edges) {
            ld from = dp[k - 1][e.from];
            if (from == inf) continue;
            ld &to = dp[k][e.to];
            to = min(to, from + e.weight);
        }

    ld ans = inf;
    for (int v = 0; v < n; ++v) if (dp[n][v] != inf) {
        ld worst = -inf;
        for (int k = 0; k < n; ++k) if (dp[k][v] != inf) {
            ld d = dp[n][v] - dp[k][v];
            worst = max(worst, d / (n - k));
        }
        ans = min(ans, worst);
    }
    return {ans != inf, ans};
}
