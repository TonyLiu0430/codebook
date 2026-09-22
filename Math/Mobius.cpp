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
