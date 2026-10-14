// needs circumcentre.cpp; expected O(n); returns {centre, radius}
pair<point, ld> smallest_circle(vector<point> p) {
    ranges::shuffle(p, mt19937(random_device{}()));
    point c;
    ld r2 = 0;
    auto outside = [&](point q) {
        return norm2(q - c) > r2 + eps;
    };
    for (int i = 0; i < ssize(p); ++i) if (outside(p[i])) {
        c = p[i], r2 = 0;
        for (int j = 0; j < i; ++j) if (outside(p[j])) {
            c = (p[i] + p[j]) * 0.5, r2 = norm2(p[i] - c);
            for (int k = 0; k < j; ++k) {
                if (!outside(p[k])) continue;
                c = circumcentre(p[i], p[j], p[k]);
                r2 = norm2(p[i] - c);
            }
        }
    }
    return {c, sqrtl(r2)};
}
