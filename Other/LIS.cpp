// 最長嚴格遞增子序列 O(n log n)，回傳子序列的索引；要非
// 嚴格遞增改用 upper_bound。
// longest strictly increasing subsequence, O(n log n)
// non-decreasing: use upper_bound; returns indices
vector<int> lis(const vector<long long> &a) {
    vector<long long> tail;
    vector<int> id, prev(a.size(), -1);
    for (int i = 0; i < ssize(a); ++i) {
        int k =
            ranges::lower_bound(tail, a[i]) - tail.begin();
        if (k == ssize(tail))
            tail.push_back(a[i]), id.push_back(i);
        else tail[k] = a[i], id[k] = i;
        if (k) prev[i] = id[k - 1];
    }
    vector<int> res;
    for (int i = id.empty() ? -1 : id.back(); i != -1;
         i = prev[i])
        res.push_back(i);
    ranges::reverse(res);
    return res;
}
