// XOR 線性基：插入數字、判斷某數能否由集合 xor 出來、求
// 子集 xor 最大值。
// xor basis; b[i] has highest bit i
using ull = unsigned long long;

struct xor_basis {
    array<ull, 64> b{};
    bool insert(ull x) { // false if x is already spanned
        for (int i = 63; i >= 0; --i) if (x >> i & 1) {
            if (!b[i]) return b[i] = x, true;
            x ^= b[i];
        }
        return false;
    }
    bool contains(ull x) {
        for (int i = 63; i >= 0; --i) if (x >> i & 1) {
            if (!b[i]) return false;
            x ^= b[i];
        }
        return true;
    }
    ull max_xor(ull x = 0) {
        for (int i = 63; i >= 0; --i) x = max(x, x ^ b[i]);
        return x;
    }
};
