// c[i op j] += a[i] * b[j]; op is '^', '&' or '|'; size is a power of two
// under a modulus replace "/= n" with "*= inverse(n)"
// SOS dp = fwht(a, '|', false); superset sum uses '&'
using ll = long long;

void fwht(vector<ll> &a, char op, bool inverse) {
    int n = a.size();
    for (int len = 1; len < n; len *= 2)
        for (int i = 0; i < n; i += 2 * len)
            for (int j = i; j < i + len; ++j) {
                ll &x = a[j], &y = a[j + len];
                if (op == '^') tie(x, y) = pair(x + y, x - y);
                else if (op == '&') x += inverse ? -y : y; // superset sum
                else y += inverse ? -x : x;                // subset sum
            }
    if (inverse && op == '^') for (ll &x : a) x /= n;
}

vector<ll> fwht_convolution(vector<ll> a, vector<ll> b, char op) {
    fwht(a, op, false), fwht(b, op, false);
    for (int i = 0; i < ssize(a); ++i) a[i] *= b[i];
    fwht(a, op, true);
    return a;
}
