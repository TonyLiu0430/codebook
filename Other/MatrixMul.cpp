// 模 mod 的矩陣乘法 O(n^3)；搭配快速冪可求線性遞迴（如
// 費氏數列）第 n 項。
using ll = long long;
using matrix = vector<vector<ll>>;

matrix multiply(const matrix &a, const matrix &b, ll mod) {
    assert(!a.empty() && !b.empty() &&
           a[0].size() == b.size());
    matrix c(a.size(), vector<ll>(b[0].size()));
    for (int i = 0; i < ssize(a); ++i)
        for (int k = 0; k < ssize(b); ++k)
            for (int j = 0; j < ssize(b[0]); ++j) {
                ll x = (__int128)a[i][k] * b[k][j] % mod;
                c[i][j] = (c[i][j] + x) % mod;
            }
    return c;
}
