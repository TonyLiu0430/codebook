using ll = long long;
using matrix = vector<vector<ll>>;

matrix multiply(const matrix &a, const matrix &b, ll mod) {
    assert(!a.empty() && !b.empty() && a[0].size() == b.size());
    matrix c(a.size(), vector<ll>(b[0].size()));
    for (int i = 0; i < ssize(a); ++i)
        for (int k = 0; k < ssize(b); ++k)
            for (int j = 0; j < ssize(b[0]); ++j)
                c[i][j] = (c[i][j] + (__int128)a[i][k] * b[k][j]) % mod;
    return c;
}
