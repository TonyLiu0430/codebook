using ll = long long;
const ll inf = LLONG_MAX / 4;

struct dinic {
    struct edge { int to, rev; ll cap; };
    vector<vector<edge>> g;
    vector<int> level, it;

    dinic(int n) : g(n), level(n), it(n) {}
    void add_edge(int u, int v, ll cap) {
        int a = g[u].size(), b = g[v].size();
        g[u].push_back({v, b, cap});
        g[v].push_back({u, a, 0});
    }
    bool bfs(int s, int t) {
        ranges::fill(level, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &e : g[u]) if (e.cap && level[e.to] == -1)
                level[e.to] = level[u] + 1, q.push(e.to);
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll flow) {
        if (u == t) return flow;
        for (int &i = it[u]; i < ssize(g[u]); ++i) {
            edge &e = g[u][i];
            if (!e.cap || level[e.to] != level[u] + 1) continue;
            ll got = dfs(e.to, t, min(flow, e.cap));
            if (!got) continue;
            e.cap -= got;
            g[e.to][e.rev].cap += got;
            return got;
        }
        return 0;
    }
    ll max_flow(int s, int t) {
        ll ans = 0, got;
        while (bfs(s, t)) {
            ranges::fill(it, 0);
            while ((got = dfs(s, t, inf))) ans += got;
        }
        return ans;
    }
    vector<char> min_cut_side(int s) {
        vector<char> seen(g.size());
        vector<int> stack{ s };
        seen[s] = true;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (auto &e : g[u]) if (e.cap && !seen[e.to])
                seen[e.to] = true, stack.push_back(e.to);
        }
        return seen;
    }
};

/*
lower bounds [low, high]:
add u->v with high-low; balance[u]-=low, balance[v]+=low.
add ss->v for positive balance, v->tt for negative balance.
for s-t flow also add t->s with inf before the feasibility flow.
after feasibility, remove ss/tt and t->s:
max = base + max_flow(s,t), min = base - max_flow(t,s).
*/
