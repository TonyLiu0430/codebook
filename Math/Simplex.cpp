// maximize c^T x subject to A x <= b, x >= 0 (two-phase simplex)
// solve() returns the optimum, inf if unbounded, -inf if infeasible
using ld = long double;

struct simplex {
    static constexpr ld eps = 1e-9, inf = numeric_limits<ld>::infinity();
    int m, n;
    vector<int> N, B;
    vector<vector<ld>> D;

    simplex(const vector<vector<ld>> &A, const vector<ld> &b, const vector<ld> &c)
        : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<ld>(n + 2)) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) D[i][j] = A[i][j];
            B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; ++j) N[j] = j, D[m][j] = -c[j];
        N[n] = -1, D[m + 1][n] = 1;
    }
    void pivot(int r, int s) {
        ld inv = 1 / D[r][s];
        for (int i = 0; i < m + 2; ++i) if (i != r && fabsl(D[i][s]) > eps) {
            ld k = D[i][s] * inv;
            for (int j = 0; j < n + 2; ++j) D[i][j] -= D[r][j] * k;
            D[i][s] = D[r][s] * k;
        }
        for (int j = 0; j < n + 2; ++j) if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; ++i) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }
    bool run(int phase) {
        for (int x = m + phase - 1;;) {
            int s = -1;
            for (int j = 0; j <= n; ++j) if (N[j] != -phase)
                if (s == -1 || pair(D[x][j], N[j]) < pair(D[x][s], N[s])) s = j;
            if (D[x][s] >= -eps) return true;
            int r = -1;
            for (int i = 0; i < m; ++i) if (D[i][s] > eps)
                if (r == -1 || pair(D[i][n + 1] / D[i][s], B[i]) <
                               pair(D[r][n + 1] / D[r][s], B[r])) r = i;
            if (r == -1) return false;
            pivot(r, s);
        }
    }
    ld solve(vector<ld> &x) {
        int r = 0;
        for (int i = 1; i < m; ++i) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (D[r][n + 1] < -eps) {
            pivot(r, n);
            if (!run(2) || D[m + 1][n + 1] < -eps) return -inf;
            for (int i = 0; i < m; ++i) if (B[i] == -1) {
                int s = 0;
                for (int j = 1; j <= n; ++j)
                    if (pair(D[i][j], N[j]) < pair(D[i][s], N[s])) s = j;
                pivot(i, s);
            }
        }
        bool ok = run(1);
        x.assign(n, 0);
        for (int i = 0; i < m; ++i) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : inf;
    }
};
