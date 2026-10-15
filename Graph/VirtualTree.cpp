// 虛樹：只保留關鍵點與它們兩兩的 LCA 建出縮小的樹，多次
// 詢問且關鍵點總數有限時做樹 DP。
// tin: dfs preorder (hld.pos works), lca: e.g. hld.lca
// returns edges (parent, child) of the virtual tree on
// keys and their lcas; the root is the first parent
vector<pair<int, int>> virtual_tree(vector<int> v,
    const vector<int> &tin, auto lca) {
    auto cmp = [&](int a, int b) {
        return tin[a] < tin[b];
    };
    ranges::sort(v, cmp);
    for (int i = 0, k = v.size(); i + 1 < k; ++i)
        v.push_back(lca(v[i], v[i + 1]));
    ranges::sort(v, cmp);
    v.erase(ranges::unique(v).begin(), v.end());
    vector<pair<int, int>> e;
    for (int i = 0; i + 1 < ssize(v); ++i)
        e.push_back({lca(v[i], v[i + 1]), v[i + 1]});
    return e;
}
