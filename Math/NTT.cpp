constexpr int P = 998244353; 
const int G = 3;
/*預處理 lim*/
int lim = 1;
while (lim < (lenSum - 1)) lim <<= 1;
/*每個多項式都要resize(lim)*/
/*998244353	3 1004535809 3 469762049 3 167772161 3 754974721 11*/
void init_rev(vector<int> &rev, int lim) {
    int lg = __builtin_ctz(lim); // lim 是 2^k
    rev.resize(lim);
    for (int i = 0; i < lim; ++i)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
}
// a.size() == lim
void ntt(vector<int> &a, int opt) { // opt == -1 => reverse ntt
    int n = a.size();
    static vector<int> rev;
    init_rev(rev, n);
    for (int i = 0; i < n; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    
    for (int m = 2; m <= n; m <<= 1) {
        int k = m >> 1;
        int gn = qpow(G, (P - 1) / m);
        if (opt == -1) gn = qpow(gn, P - 2);
        for (int i = 0; i < n; i += m) {
            int g = 1;
            for (int j = 0; j < k; ++j) {
                int t = 1ll * a[i + j + k] * g % P;
                a[i + j + k] = (a[i + j] - t + P) % P;
                a[i + j] = (a[i + j] + t) % P;
                g = 1ll * g * gn % P;
            }
        }
    }

    if (opt == -1) {
        int inv_n = qpow(n, P - 2);
        for (int &x : a) x = 1ll * x * inv_n % P;
    }
}