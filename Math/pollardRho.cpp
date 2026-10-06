// needs is_prime() and mod_mul() from Miller-Rabin.cpp
using u64 = uint64_t;

u64 pollard(u64 n) {
    if (!(n & 1)) return 2;
    static mt19937_64 rng(time(0));
    while (true) {
        u64 c = rng() % (n - 1) + 1;
        u64 x = rng() % n, y = x, d = 1;
        auto f = [&](u64 v) { return (__uint128_t(mod_mul(v, v, n)) + c) % n; };
        while (d == 1) {
            x = f(x), y = f(f(y));
            d = gcd(x > y ? x - y : y - x, n);
        }
        if (d != n) return d;
    }
}

void factor(u64 n, map<u64, int> &count) {
    if (n == 1) return;
    if (is_prime(n)) return ++count[n], void();
    u64 d = pollard(n);
    factor(d, count);
    factor(n / d, count);
}
