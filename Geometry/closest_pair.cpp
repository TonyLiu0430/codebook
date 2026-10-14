// needs 2Dpoint.cpp; O(n log n), returns the squared distance, n >= 2
ld closest_pair(vector<point> p) {
    ranges::sort(p, {}, &point::x);
    set<pair<ld, ld>> s; // (y, x)
    ld best = numeric_limits<ld>::max();
    for (int i = 0, j = 0; i < ssize(p); ++i) {
        ld d = sqrtl(best);
        while (p[i].x - p[j].x > d)
            s.erase({p[j].y, p[j].x}), ++j;
        ld top = p[i].y + d;
        auto it = s.lower_bound({p[i].y - d, -HUGE_VALL});
        for (; it != s.end() && it->first <= top; ++it) {
            point q{it->second, it->first};
            best = min(best, norm2(p[i] - q));
        }
        s.insert({p[i].y, p[i].x});
    }
    return best;
}
