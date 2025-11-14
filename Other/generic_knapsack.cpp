struct Item {
    int w, v, c;
};

vector<int> dp(W + 1, 0);
for (auto &it : items) {
    int w = it.w, v = it.v, c = it.c;
    if (w == 0) continue;
    for (int r = 0; r < w; ++r) {
        deque<pair<int, int>> dq;
        // dq: (value, index k)

        for (int k = 0, j = r; j <= W; ++k, j += w) {
            // push dp[j] - k*v
            int val = dp[j] - k * v;

            while (!dq.empty() && dq.back().first <= val)
                dq.pop_back();
            dq.emplace_back(val, k);

            // pop front if k - dq.front().second > c
            while (dq.front().second < k - c)
                dq.pop_front();

            dp[j] = dq.front().first + k * v;
        }
    }
}