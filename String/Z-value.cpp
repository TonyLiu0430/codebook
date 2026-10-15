// Z function：z[i] 為 s 與 s[i..] 的最長共同前綴長度；
vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
// Manacher O(n)：奇數回文半徑，包含中心
vector<int> manacher_odd(const string &s) {
    int n = s.size();
    vector<int> radius(n);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k =
            i > r ? 1 : min(radius[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n &&
               s[i - k] == s[i + k])
            ++k;
        radius[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    return radius;
}
// 奇偶共用：string t="#"; for(char c:s) t+=c,t+='#';
// auto d=manacher_odd(t); // 原字串回文長度 d[i]-1
// 起點 (i-d[i]+1)/2；例如 abba -> #a#b#b#a#
