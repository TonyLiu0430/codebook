// needs 2Dpoint.cpp; O(n log n), returns the squared distance, n >= 2
ld closest_pair(vector<point> p) {
    ranges::sort(p, {}, &point::x);
    set<pair<ld, ld>> s; // (y, x)
    ld best = numeric_limits<ld>::max();
    for (int i = 0, j = 0; i < ssize(p); ++i) {
        ld d = sqrtl(best);
        while (p[i].x - p[j].x > d) s.erase({p[j].y, p[j].x}), ++j;
        auto it = s.lower_bound({p[i].y - d, -numeric_limits<ld>::max()});
        for (; it != s.end() && it->first <= p[i].y + d; ++it)
            best = min(best, norm2(p[i] - point{it->second, it->first}));
        s.insert({p[i].y, p[i].x});
    }
    return best;
}
