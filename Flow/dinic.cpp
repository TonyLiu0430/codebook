// Dinic 最大流，另可取得最小割的 S 側點集。二分圖匹配、
// 最小割建模都用它。
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
            for (auto &e : g[u])
                if (e.cap && level[e.to] == -1)
                    level[e.to] = level[u] + 1,
                    q.push(e.to);
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll flow) {
        if (u == t) return flow;
        for (int &i = it[u]; i < ssize(g[u]); ++i) {
            edge &e = g[u][i];
            if (!e.cap || level[e.to] != level[u] + 1)
                continue;
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
上下界 [low, high]：u->v 容量改為 high-low。
balance[u]-=low，balance[v]+=low。
正接 ss->v、負接 v->tt，容量為 balance 絕對值。
有源匯時先加 t->s 容量 inf，再跑 ss->tt 可行流。
ss 出邊須滿流；base 為 t->s 流量。
移除 ss/tt、t->s 及其反向邊，於殘量圖擇一：
最大 = base + max_flow(s,t)，最小 = base - max_flow(t,s)。
*/
