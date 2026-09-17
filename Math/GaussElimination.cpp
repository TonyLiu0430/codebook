using ld = long double;
const ld eps = 1e-12L;

// augmented matrix; returns 0=no solution, 1=unique, 2=infinite
int gauss(vector<vector<ld>> a, vector<ld> &answer) {
    int n = a.size(), m = a.empty() ? 0 : a[0].size() - 1, row = 0;
    vector<int> where(m, -1);
    for (int col = 0; col < m && row < n; ++col) {
        int best = row;
        for (int i = row; i < n; ++i)
            if (fabsl(a[i][col]) > fabsl(a[best][col])) best = i;
        if (fabsl(a[best][col]) <= eps) continue;
        swap(a[best], a[row]);
        where[col] = row;
        ld div = a[row][col];
        for (int j = col; j <= m; ++j) a[row][j] /= div;
        for (int i = 0; i < n; ++i) if (i != row) {
            ld mul = a[i][col];
            for (int j = col; j <= m; ++j) a[i][j] -= mul * a[row][j];
        }
        ++row;
    }
    answer.assign(m, 0);
    for (int i = 0; i < m; ++i) if (where[i] != -1)
        answer[i] = a[where[i]][m];
    for (auto &r : a) {
        ld sum = 0;
        for (int i = 0; i < m; ++i) sum += r[i] * answer[i];
        if (fabsl(sum - r[m]) > eps) return 0;
    }
    return count(where.begin(), where.end(), -1) ? 2 : 1;
}
