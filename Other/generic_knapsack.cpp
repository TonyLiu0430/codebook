using ll = long long;

struct item {
    int weight, count;
    ll value;
};

// dp[w] = maximum value with total weight at most w
vector<ll> bounded_knapsack(int capacity, const vector<item> &items) {
    vector<ll> dp(capacity + 1);
    for (item x : items) {
        assert(x.weight >= 0 && x.count >= 0);
        if (!x.weight) {
            if (x.value > 0)
                for (ll &value : dp) value += x.value * x.count;
            continue;
        }
        for (int r = 0; r < x.weight && r <= capacity; ++r) {
            deque<pair<ll, int>> q;
            for (int k = 0, w = r; w <= capacity; ++k, w += x.weight) {
                ll value = dp[w] - ll(k) * x.value;
                while (!q.empty() && q.back().first <= value) q.pop_back();
                q.push_back({value, k});
                while (q.front().second < k - x.count) q.pop_front();
                dp[w] = q.front().first + ll(k) * x.value;
            }
        }
    }
    return dp;
}
