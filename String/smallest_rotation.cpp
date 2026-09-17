string smallest_rotation(string s) {
    int n = s.size();
    if (!n) return s;
    s += s;
    int i = 0, j = 1;
    while (i < n && j < n) {
        int k = 0;
        while (k < n && s[i + k] == s[j + k]) ++k;
        if (k == n) break;
        if (s[i + k] < s[j + k]) j += k + 1;
        else i += k + 1;
        if (i == j) ++j;
    }
    return s.substr(min(i, j), n);
}
