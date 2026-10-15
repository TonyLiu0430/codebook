// 線性篩（歐拉篩）O(n) 求 <= n 的所有質數，每個合數只被
// 最小質因數篩一次。
// 內部 min_prime[] 是最小質因數，留著可 O(log n) 質因數
// 分解；同架構也能順便篩 phi、mu 等積性函數。
vector<int> linear_sieve(int n) {
    vector<int> primes, min_prime(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (!min_prime[i])
            min_prime[i] = i, primes.push_back(i);
        for (int p : primes) {
            if (p > min_prime[i] || (long long)i * p > n)
                break;
            min_prime[i * p] = p;
        }
    }
    return primes;
}
