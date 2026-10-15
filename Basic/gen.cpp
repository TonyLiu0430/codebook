// 隨機測資：./gen seed，同一個 seed 產生同一組測資，
// WA 時可重現。測資開小，錯了才好手算。
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(atoi(argv[1]));
    auto rnd = [&](int l, int r) {
        return int(rng() % (r - l + 1)) + l;
    };
    int n = rnd(1, 8);
    cout << n << '\n';
    for (int i = 0; i < n; ++i) cout << rnd(1, 10) << ' ';
    cout << '\n';
}
