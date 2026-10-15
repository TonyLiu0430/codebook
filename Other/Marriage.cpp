// 穩定婚姻問題 (Gale-Shapley)：依偏好求一組不存在私奔對
// 的穩定配對。
// preference[a][rank] = b; order[b][a] = rank
vector<int>
stable_marriage(const vector<vector<int>> &preference,
                const vector<vector<int>> &order) {
    int n = preference.size();
    vector<int> next(n), partner(n, -1);
    queue<int> free;
    for (int a = 0; a < n; ++a) free.push(a);
    while (!free.empty()) {
        int a = free.front();
        free.pop();
        int b = preference[a][next[a]++];
        if (partner[b] == -1) partner[b] = a;
        else if (order[b][a] < order[b][partner[b]])
            free.push(partner[b]), partner[b] = a;
        else free.push(a);
    }
    return partner; // partner[b] = a
}
