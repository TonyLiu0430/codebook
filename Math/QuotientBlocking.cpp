// 數論分塊（整除分塊）：floor(n/i) 只有 O(sqrt(n)) 種值，
// 值相同的 i 連成一段，一段一起算。
// 一段從 l 開始：值 q = n / l，右端點 r = n / q。
// pre(x) = f(1) + ... + f(x)（f 的前綴和），pre(0) = 0；
// 每段貢獻 (pre(r) - pre(l - 1)) * q。
// 例：f = 1 時 pre = [](ll x) { return x; }
//     gcd(i, j) = 1 的對數：sum_floor_product 配 mu 前綴和
// 取模時把 pre 差值與乘法改成模運算。
using ll = long long;
using i128 = __int128;

// sum_{i=1..n} f(i) * floor(n / i)，n >= 0
i128 sum_floor(ll n, auto &&pre) {
    i128 ans = 0;
    for (ll l = 1, r; l <= n; l = r + 1) {
        ll q = n / l;
        r = n / q;
        ans += (i128)(pre(r) - pre(l - 1)) * q;
        if (r == n)
            break; // 避免 n == LLONG_MAX 時 r + 1 溢位
    }
    return ans;
}

// sum_{i=1..min(n,m)} f(i) * floor(n / i) * floor(m / i)
// 兩個值都要不變，右端點取 min
i128 sum_floor_product(ll n, ll m, auto &&pre) {
    ll limit = min(n, m);
    i128 ans = 0;
    for (ll l = 1, r; l <= limit; l = r + 1) {
        ll qn = n / l, qm = m / l;
        r = min(n / qn, m / qm);
        ans += (i128)(pre(r) - pre(l - 1)) * qn * qm;
        if (r == limit) break;
    }
    return ans;
}
