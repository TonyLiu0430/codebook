// CYK 最小代價推導 O(n^3 |規則|)；文法任意，不含 ε 規則
// 大寫字母 = 非終端，其他字元 = 終端；長規則自動拆成 CNF
// add('S', "aSb", w)：S -> aSb 代價 w
// solve(s, 'S')：S 推出 s 的最小代價，推不出回傳 inf
// 單位規則 A -> B 不能有負環
using ll = long long;
const ll inf = LLONG_MAX / 4;

struct cyk {
    struct rule { int a, b, c; ll w; }; // a -> b c
    int n = 26; // 非終端數，拆規則產生的從 26 開始
    vector<rule> bin, unit;            // unit：a -> b
    vector<tuple<int, char, ll>> term; // a -> ch
    map<char, int> tid;
    int sym(char ch) { // 長規則裡的終端換成 X -> ch
        if (isupper(ch)) return ch - 'A';
        if (!tid.count(ch))
            tid[ch] = n, term.push_back({n++, ch, 0});
        return tid[ch];
    }
    void add(char A, string rhs, ll w) {
        int a = A - 'A';
        char x = rhs[0];
        if (rhs.size() == 1 && isupper(x))
            return unit.push_back({a, x - 'A', -1, w});
        if (rhs.size() == 1)
            return term.push_back({a, x, w});
        vector<int> v;
        for (char ch : rhs) v.push_back(sym(ch));
        for (int i = 0; i + 2 < ssize(v); ++i)
            bin.push_back({a, v[i], n, 0}), a = n++;
        bin.push_back({a, v.end()[-2], v.back(), w});
    }
    ll solve(const string &s, char S) {
        int m = s.size();
        if (!m) return inf;
        vector dp(m, vector(m, vector<ll>(n, inf)));
        for (int len = 1; len <= m; ++len)
        for (int l = 0, r = len - 1; r < m; ++l, ++r) {
            auto &d = dp[l][r];
            auto upd = [&](int a, ll v) {
                d[a] = min(d[a], v);
            };
            if (len == 1)
                for (auto [a, ch, w] : term)
                    if (ch == s[l]) upd(a, w);
            for (int k = l; k < r; ++k)
                for (auto [a, b, c, w] : bin) {
                    ll x = dp[l][k][b];
                    ll y = dp[k + 1][r][c];
                    if (x < inf && y < inf)
                        upd(a, x + y + w);
                }
            for (int it = 0; it < n; ++it) // 單位規則鬆弛
                for (auto [a, b, c, w] : unit)
                    if (d[b] < inf) upd(a, d[b] + w);
        }
        return dp[0][m - 1][S - 'A'];
    }
};
