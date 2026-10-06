// 回傳字典序最小的循環位移，O(n)
// 例如 "baca" -> "abac"；將開頭若干字元搬到尾端
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
