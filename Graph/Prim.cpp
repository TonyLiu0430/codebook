using ll = long long;
using edge = pair<ll, int>; // weight, to

// {connected, mst weight}; zero and parallel edges are allowed
pair<bool, ll> prim(const vector<vector<edge>> &g, int root = 0) {
    if (g.empty()) return {true, 0};
    vector<char> used(g.size());
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    pq.push({0, root});
    ll total = 0;
    int seen = 0;
    while (!pq.empty()) {
        ll w = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (used[u]) continue;
        used[u] = true;
        total += w;
        ++seen;
        for (edge e : g[u]) if (!used[e.second]) pq.push(e);
    }
    return {seen == (int)g.size(), total};
}
