using u64 = uint64_t;
using u128 = __uint128_t;

u64 mod_mul(u64 a, u64 b, u64 mod) { return u128(a) * b % mod; }
u64 mod_power(u64 a, u64 n, u64 mod) {
    u64 ans = 1;
    for (; n; n /= 2, a = mod_mul(a, a, mod))
        if (n & 1) ans = mod_mul(ans, a, mod);
    return ans;
}

bool is_prime(u64 n) {
    if (n < 2) return false;
    for (u64 p : array<u64, 7>{2, 3, 5, 7, 11, 13, 17}) {
        if (n % p == 0) return n == p;
    }
    u64 d = n - 1, s = 0;
    while (!(d & 1)) d /= 2, ++s;
    for (u64 a : array<u64, 7>{2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0) continue;
        u64 x = mod_power(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (u64 r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
