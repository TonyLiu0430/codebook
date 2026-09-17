using ll = long long;
const ll inf = LLONG_MAX / 4;

struct min_cost_flow {
    struct edge { int to, rev; ll cap, cost; };
    vector<vector<edge>> g;

    min_cost_flow(int n) : g(n) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        int a = g[u].size(), b = g[v].size();
        g[u].push_back({v, b, cap, cost});
        g[v].push_back({u, a, 0, -cost});
    }
    pair<ll, ll> solve(int s, int t, ll limit = inf) {
        ll flow = 0, cost = 0;
        int n = g.size();
        vector<ll> dist(n);
        vector<int> pv(n), pe(n);
        vector<char> in_queue(n);
        while (flow < limit) {
            fill(dist.begin(), dist.end(), inf);
            fill(in_queue.begin(), in_queue.end(), false);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            in_queue[s] = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in_queue[u] = false;
                for (int i = 0; i < (int)g[u].size(); ++i) {
                    edge &e = g[u][i];
                    __int128 raw = (__int128)dist[u] + e.cost;
                    ll nd = raw < -inf ? -inf : raw > inf ? inf : (ll)raw;
                    if (e.cap && dist[e.to] > nd) {
                        dist[e.to] = nd;
                        pv[e.to] = u, pe[e.to] = i;
                        if (!in_queue[e.to]) q.push(e.to), in_queue[e.to] = true;
                    }
                }
            }
            if (dist[t] == inf) break;
            ll add = limit - flow;
            for (int v = t; v != s; v = pv[v]) add = min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                edge &e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            flow += add;
            cost += add * dist[t];
        }
        return {flow, cost};
    }
};
