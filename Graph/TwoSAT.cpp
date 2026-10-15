// 2-SAT：每個布林變數二選一、限制為「a 或 b」形式，以
// SCC 判斷可滿足並求出一組解。
// variable x: node 2x means x is true, 2x+1 means x is false
struct two_sat {
    int n, time = 0, count = 0;
    vector<vector<int>> g;
    vector<int> dfn, low, comp, stack;

    two_sat(int n) : n(n), g(2 * n) {}
    // (x == a) or (y == b)
    void either(int x, bool a, int y, bool b) {
        int u = 2 * x + !a, v = 2 * y + !b;
        g[u ^ 1].push_back(v);
        g[v ^ 1].push_back(u);
    }
    void implies(int x, bool a, int y, bool b) {
        either(x, !a, y, b);
    }
    void set(int x, bool a) { either(x, a, x, a); }
    void dfs(int u) {
        dfn[u] = low[u] = ++time;
        stack.push_back(u);
        for (int v : g[u]) {
            if (!dfn[v])
                dfs(v), low[u] = min(low[u], low[v]);
            else if (comp[v] == -1)
                low[u] = min(low[u], dfn[v]);
        }
        if (low[u] != dfn[u]) return;
        for (int v = -1; v != u; stack.pop_back())
            comp[v = stack.back()] = count;
        ++count;
    }
    // nullopt if unsatisfiable
    optional<vector<bool>> solve() {
        dfn.assign(2 * n, 0), low.assign(2 * n, 0);
        comp.assign(2 * n, -1);
        for (int i = 0; i < 2 * n; ++i)
            if (!dfn[i]) dfs(i);
        vector<bool> ans(n);
        for (int i = 0; i < n; ++i) {
            if (comp[2 * i] == comp[2 * i + 1])
                return nullopt;
            // tarjan numbers SCCs in reverse topological order
            ans[i] = comp[2 * i] < comp[2 * i + 1];
        }
        return ans;
    }
};
