// maximum cardinality bipartite matching
struct bipartite_matching {
    vector<vector<int>> g;
    vector<int> right_match, seen;
    int stamp = 0;

    bipartite_matching(int left, int right)
        : g(left), right_match(right, -1), seen(right) {}
    void add_edge(int left, int right) { g[left].push_back(right); }
    bool dfs(int u) {
        for (int v : g[u]) if (seen[v] != stamp) {
            seen[v] = stamp;
            if (right_match[v] == -1 || dfs(right_match[v]))
                return right_match[v] = u, true;
        }
        return false;
    }
    int solve() {
        int ans = 0;
        for (int u = 0; u < (int)g.size(); ++u) ++stamp, ans += dfs(u);
        return ans;
    }
};
