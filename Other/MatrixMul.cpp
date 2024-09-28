#define MOD INT_MAX
vector<vector<int>> operator *(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    vector<vector<int>> re(a.size(), vector<int>(b[0].size()));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b[0].size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                re[i][j] += (a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return re;
}