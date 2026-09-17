/*
finite impartial game:
sg[u] = mex({sg[v] | u -> v}).
xor the sg values only when combining independent games.
normal play: xor != 0 wins.
misere nim: if every pile is 1, odd pile count loses; otherwise xor != 0 wins.
*/
vector<int> grundy(const vector<vector<int>> &g) {
    vector<int> sg(g.size(), -1);
    function<int(int)> dfs = [&](int u) {
        if (sg[u] != -1) return sg[u];
        vector<int> seen(g[u].size() + 1);
        for (int v : g[u]) {
            int x = dfs(v);
            if (x < (int)seen.size()) seen[x] = true;
        }
        return sg[u] = find(seen.begin(), seen.end(), 0) - seen.begin();
    };
    for (int u = 0; u < (int)g.size(); ++u) dfs(u);
    return sg;
}
