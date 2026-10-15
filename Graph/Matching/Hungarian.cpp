// 二分圖最大匹配（Kuhn 逐點增廣），O(VE)，程式短。
// 可控制增廣順序：左點依權重由大到小 dfs，得到「被配到
// 的左點權重和最大」；也可做字典序最小、逐點加入的增量
// 匹配（HK 是整批增廣，做不到）。
struct bipartite_matching {
    vector<vector<int>> g;
    vector<int> right_match, seen;
    int stamp = 0;

    bipartite_matching(int left, int right)
        : g(left), right_match(right, -1), seen(right) {}
    void add_edge(int left, int right) {
        g[left].push_back(right);
    }
    bool dfs(int u) {
        for (int v : g[u]) if (seen[v] != stamp) {
            seen[v] = stamp;
            if (right_match[v] == -1 ||
                dfs(right_match[v]))
                return right_match[v] = u, true;
        }
        return false;
    }
    int solve() {
        int ans = 0;
        for (int u = 0; u < ssize(g); ++u)
            ++stamp, ans += dfs(u);
        return ans;
    }
};
