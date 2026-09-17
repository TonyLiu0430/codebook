struct suffix_data {
    vector<int> sa, rank, lcp;
};

suffix_data suffix_array(const string &s) {
    int n = s.size();
    if (!n) return {};
    vector<int> sa(n), rank(n), next(n), temp(n), count(max(n, 256));

    for (unsigned char c : s) ++count[c];
    partial_sum(count.begin(), count.end(), count.begin());
    for (int i = n - 1; i >= 0; --i) sa[--count[(unsigned char)s[i]]] = i;
    int classes = 0;
    for (int i = 0; i < n; ++i) {
        if (i && s[sa[i]] != s[sa[i - 1]]) ++classes;
        rank[sa[i]] = classes;
    }
    ++classes;

    for (int len = 1; len < n && classes < n; len *= 2) {
        int p = 0;
        for (int i = max(0, n - len); i < n; ++i) temp[p++] = i;
        for (int x : sa) if (x >= len) temp[p++] = x - len;

        fill(count.begin(), count.begin() + classes, 0);
        for (int x : temp) ++count[rank[x]];
        partial_sum(count.begin(), count.begin() + classes, count.begin());
        for (int i = n - 1; i >= 0; --i)
            sa[--count[rank[temp[i]]]] = temp[i];

        next[sa[0]] = 0;
        int new_classes = 1;
        for (int i = 1; i < n; ++i) {
            int a = sa[i - 1], b = sa[i];
            int ar = a + len < n ? rank[a + len] : -1;
            int br = b + len < n ? rank[b + len] : -1;
            if (rank[a] != rank[b] || ar != br) ++new_classes;
            next[b] = new_classes - 1;
        }
        rank.swap(next);
        classes = new_classes;
    }

    vector<int> lcp(n);
    for (int i = 0, h = 0; i < n; ++i) {
        if (!rank[i]) continue;
        int j = sa[rank[i] - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
        lcp[rank[i]] = h;
        if (h) --h;
    }
    return {sa, rank, lcp};
}
