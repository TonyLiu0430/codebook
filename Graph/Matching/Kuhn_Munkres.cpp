using ll = long long;
const ll missing = LLONG_MIN / 4;
const ll inf = LLONG_MAX / 4;

struct assignment_result {
    bool perfect;
    ll weight;
    vector<int> right_match;
};

// square maximum-weight assignment; use missing for absent edges
assignment_result max_weight_matching(const vector<vector<ll>> &weight) {
    int n = weight.size();
    for (auto &row : weight) assert((int)row.size() == n);
    vector<ll> u(n + 1), v(n + 1);
    vector<int> p(n + 1), way(n + 1);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        vector<ll> best(n + 1, inf);
        vector<char> used(n + 1);
        int col = 0;
        do {
            used[col] = true;
            int row = p[col], next = 0;
            ll delta = inf;
            for (int j = 1; j <= n; ++j) if (!used[j]) {
                ll cost = weight[row - 1][j - 1] == missing
                        ? inf / 2 : -weight[row - 1][j - 1];
                ll cur = cost - u[row] - v[j];
                if (cur < best[j]) best[j] = cur, way[j] = col;
                if (best[j] < delta) delta = best[j], next = j;
            }
            for (int j = 0; j <= n; ++j)
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else best[j] -= delta;
            col = next;
        } while (p[col]);
        do {
            int prev = way[col];
            p[col] = p[prev];
            col = prev;
        } while (col);
    }

    vector<int> match(n, -1);
    ll sum = 0;
    for (int col = 1; col <= n; ++col) {
        int row = p[col] - 1;
        match[col - 1] = row;
        if (weight[row][col - 1] == missing) return {false, 0, {}};
        sum += weight[row][col - 1];
    }
    return {true, sum, match};
}
