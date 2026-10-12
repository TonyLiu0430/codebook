using ll = long long;
using i128 = __int128;

// 數論分塊（整除分塊），n >= 0，O(sqrt(n))。
// q = n / l 時，floor(n / i) 在 [l, r] 相同，r = n / q。
// sum f(i) * floor(n / i)：每塊貢獻為 (F(r) - F(l-1)) * q，
// 其中 F 是 f 的前綴和。以下範例取 f(i) = 1。
// 回傳 sum_{i=1..n} floor(n / i)。
i128 sum_floor(ll n) {
    i128 ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll q = n / l;
        r = n / q;
        ans += (i128)(r - l + 1) * q;
        if (r == n) break; // 避免 n == LLONG_MAX 時 r + 1 溢位
    }
    return ans;
}

// 雙商值分塊，n, m >= 0，O(sqrt(n) + sqrt(m))。
// 同時維持 floor(n / i)、floor(m / i) 不變，
// 右界取 min(n / (n / l), m / (m / l))。
// 回傳 sum_{i=1..min(n,m)} floor(n / i) * floor(m / i)。
// 若有權重 f(i)，將 (r - l + 1) 換成 F(r) - F(l-1)。
i128 sum_floor_product(ll n, ll m) {
    ll limit = n < m ? n : m;
    i128 ans = 0;
    for (ll l = 1, r; l <= limit; l = r + 1) {
        ll qn = n / l, qm = m / l;
        ll rn = n / qn, rm = m / qm;
        r = rn < rm ? rn : rm;
        ans += (i128)(r - l + 1) * qn * qm;
        if (r == limit) break;
    }
    return ans;
}
