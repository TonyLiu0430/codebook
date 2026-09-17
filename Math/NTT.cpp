// coefficients must be in [0, mod)
const int mod = 998244353, root = 3;

int power(int a, int n) {
    long long ans = 1;
    for (; n; n /= 2, a = (long long)a * a % mod)
        if (n & 1) ans = ans * a % mod;
    return ans;
}

void ntt(vector<int> &a, bool inverse) {
    int n = a.size();
    assert(n && !(n & (n - 1)) && (mod - 1) % n == 0);
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n / 2;
        for (; j & bit; bit /= 2) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len *= 2) {
        int wlen = power(root, (mod - 1) / len);
        if (inverse) wlen = power(wlen, mod - 2);
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; ++j) {
                int u = a[i + j], v = w * a[i + j + len / 2] % mod;
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = w * wlen % mod;
            }
        }
    }
    if (inverse) {
        int inv = power(n, mod - 2);
        for (int &x : a) x = (long long)x * inv % mod;
    }
}

vector<int> convolution(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n *= 2;
    assert(n <= (1 << 23));
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] = (long long)a[i] * b[i] % mod;
    ntt(a, true);
    a.resize(need);
    return a;
}
