// needs 2Dpoint.cpp; polygon vertices are given in order
// signed area, ccw is positive
ld polygon_area(const vector<point> &p) {
    ld s = 0;
    for (int i = 0, n = p.size(); i < n; ++i)
        s += cross(p[i], p[(i + 1) % n]);
    return s / 2;
}

ld segment_distance(point a, point b, point q) {
    point d = b - a;
    if (norm2(d) <= eps) return norm(q - a);
    ld t = clamp(dot(q - a, d) / norm2(d), ld(0), ld(1));
    return norm(q - (a + d * t));
}

// 1 inside, 0 on boundary, -1 outside
int point_in_polygon(const vector<point> &p, point q) {
    bool in = false;
    for (int i = 0, n = p.size(); i < n; ++i) {
        point a = p[i], b = p[(i + 1) % n];
        if (segment_distance(a, b, q) <= eps) return 0;
        if ((a.y > q.y) == (b.y > q.y)) continue;
        ld t = (q.y - a.y) / (b.y - a.y);
        if (q.x < a.x + (b.x - a.x) * t) in = !in;
    }
    return in ? 1 : -1;
}

// squared diameter by rotating calipers; h is ccw from convex_hull
ld diameter2(const vector<point> &h) {
    int n = h.size();
    ld best = 0;
    for (int i = 0, j = 1 % max(n, 1); i < n; ++i) {
        point e = h[(i + 1) % n] - h[i];
        while (cross(e, h[(j + 1) % n] - h[j]) > eps)
            j = (j + 1) % n;
        best = max({best, norm2(h[i] - h[j]),
                    norm2(h[(i + 1) % n] - h[j])});
    }
    return best;
}
