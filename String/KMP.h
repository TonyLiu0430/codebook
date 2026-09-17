vector<int> prefix_function(const string &s) {
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); ++i) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp(const string &text, const string &pattern) {
    if (pattern.empty()) return {};
    vector<int> pi = prefix_function(pattern), pos;
    for (int i = 0, j = 0; i < (int)text.size(); ++i) {
        while (j && text[i] != pattern[j]) j = pi[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == (int)pattern.size()) {
            pos.push_back(i - j + 1);
            j = pi[j - 1];
        }
    }
    return pos;
}
