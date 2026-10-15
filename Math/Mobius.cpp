// 線性篩求莫比烏斯函數 mu(1..n)。
// mu(n)：n=1 為 1；n 有平方因數為 0；否則為 (-1)^(質因
// 數個數)。
// 用於莫比烏斯反演，例如計算 gcd(i,j)=1 的對數：sum_d
// mu(d) floor(n/d) floor(m/d)，常搭配數論分塊。
vector<int> mobius(int n) {
    vector<int> mu(n + 1), primes;
    vector<char> composite(n + 1);
    if (n < 1) return mu;
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!composite[i]) primes.push_back(i), mu[i] = -1;
        for (int p : primes) {
            if ((long long)i * p > n) break;
            composite[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}
