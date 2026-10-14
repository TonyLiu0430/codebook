// floating fft; exact while every result value < about 1e15
using ll = long long;
using cd = complex<double>;

void fft(vector<cd> &a, bool inverse) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n / 2;
        for (; j & bit; bit /= 2) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    vector<cd> root(n / 2);
    for (int i = 0; i < n / 2; ++i)
        root[i] = polar(1.0, 2 * numbers::pi * i / n);
    for (int len = 2; len <= n; len *= 2)
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < len / 2; ++j) {
                cd w = root[n / len * j];
                if (inverse) w = conj(w);
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v, a[i + j + len / 2] = u - v;
            }
    if (inverse) for (cd &x : a) x /= n;
}

vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n *= 2;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    fft(fa, true);
    vector<ll> c(need);
    for (int i = 0; i < need; ++i) c[i] = llround(fa[i].real());
    return c;
}
