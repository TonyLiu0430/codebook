using u64 = uint64_t;
using u128 = __uint128_t;
const u64 mod = (1ULL << 61) - 1;

u64 mod_add(u64 a, u64 b) {
    u64 x = a + b;
    return x >= mod ? x - mod : x;
}
u64 mod_mul(u64 a, u64 b) { return u128(a) * b % mod; }

struct rolling_hash {
    u64 base;
    vector<u64> hash, power;

    rolling_hash(const string &s, u64 base = 911382323) : base(base) {
        assert(1 < base && base < mod);
        hash.resize(s.size() + 1);
        power.assign(s.size() + 1, 1);
        for (int i = 0; i < (int)s.size(); ++i) {
            power[i + 1] = mod_mul(power[i], base);
            hash[i + 1] = mod_add(mod_mul(hash[i], base), (unsigned char)s[i] + 1);
        }
    }
    u64 get(int l, int r) const { // [l, r]
        u64 cut = mod_mul(hash[l], power[r - l + 1]);
        return hash[r + 1] >= cut ? hash[r + 1] - cut : hash[r + 1] + mod - cut;
    }
};
