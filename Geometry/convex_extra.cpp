// 凸包 O(log n) 點包含查詢、直線與圓交點、點到圓的切點、
// Minkowski 和（兩凸包相加）。
// needs 2Dpoint.cpp
int sign(ld x) { return (x > eps) - (x < -eps); }

// h: ccw convex, no three collinear, size >= 3, O(log n)
// 1 inside, 0 on boundary, -1 outside
int in_convex(const vector<point> &h, point q) {
    int n = h.size(), l = 1, r = n - 1;
    auto side = [&](point a, point b) {
        return sign(cross(b - a, q - a));
    };
    if (side(h[0], h[1]) < 0 || side(h[0], h[n - 1]) > 0)
        return -1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        (side(h[0], h[m]) >= 0 ? l : r) = m;
    }
    int s = side(h[l], h[l + 1]);
    if (s <= 0) return s;
    if (l == 1 && !side(h[0], h[1])) return 0;
    if (l == n - 2 && !side(h[0], h[n - 1])) return 0;
    return 1;
}

// line through a != b and circle (o, r)
vector<point> circle_line(point o, ld r, point a,
                          point b) {
    point d = b - a;
    point h = a + d * (dot(o - a, d) / norm2(d)); // foot
    ld s = r * r - norm2(o - h);
    if (s < -eps) return {};
    if (s <= eps) return {h};
    point off = d * (sqrtl(s) / norm(d));
    return {h - off, h + off};
}

// tangent points on circle (o, r) seen from p
vector<point> tangents(point o, ld r, point p) {
    point d = p - o;
    ld d2 = norm2(d);
    if (d2 < r * r - eps) return {};
    if (d2 <= r * r + eps) return {p};
    ld a = r * r / d2, b = r * sqrtl(d2 - r * r) / d2;
    point perp{-d.y, d.x};
    return {o + d * a + perp * b, o + d * a - perp * b};
}

// p, q: ccw convex polygons; result is ccw convex
vector<point> minkowski(vector<point> p, vector<point> q) {
    auto fix = [](vector<point> &v) {
        ranges::rotate(v, ranges::min_element(v, {},
            [](point a) { return pair(a.y, a.x); }));
        v.push_back(v[0]), v.push_back(v[1]);
    };
    fix(p), fix(q);
    vector<point> res;
    for (size_t i = 0, j = 0;
         i + 2 < p.size() || j + 2 < q.size();) {
        res.push_back(p[i] + q[j]);
        ld c = cross(p[i + 1] - p[i], q[j + 1] - q[j]);
        if (c >= -eps && i + 2 < p.size()) ++i;
        if (c <= eps && j + 2 < q.size()) ++j;
    }
    return res;
}
