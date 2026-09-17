vector<int> linear_sieve(int n) {
    vector<int> primes, min_prime(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (!min_prime[i]) min_prime[i] = i, primes.push_back(i);
        for (int p : primes) {
            if (p > min_prime[i] || (long long)i * p > n) break;
            min_prime[i * p] = p;
        }
    }
    return primes;
}
