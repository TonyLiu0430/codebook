using ll = long long;
using matrix = vector<vector<ll>>;

matrix multiply(const matrix &a, const matrix &b, ll mod) {
    assert(!a.empty() && !b.empty() && a[0].size() == b.size());
    matrix c(a.size(), vector<ll>(b[0].size()));
    for (int i = 0; i < (int)a.size(); ++i)
        for (int k = 0; k < (int)b.size(); ++k)
            for (int j = 0; j < (int)b[0].size(); ++j)
                c[i][j] = (c[i][j] + (__int128)a[i][k] * b[k][j]) % mod;
    return c;
}
