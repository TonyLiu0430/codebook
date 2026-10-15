// 半平面交：求所有有向直線左側區域的交集（凸多邊形），
// 可解多邊形核、線性約束可行域。
// needs 2Dpoint.cpp; keeps the left side of every directed line
// returns a ccw polygon, empty if the area is empty
// the result may be unbounded: add a large bounding box first
struct line {
    point p, v; // p + t * v
    ld angle() const { return atan2l(v.y, v.x); }
};
bool on_left(line l, point q) {
    return cross(l.v, q - l.p) > eps;
}
point line_intersection(line a, line b) {
    return a.p +
           a.v * (cross(b.v, b.p - a.p) / cross(b.v, a.v));
}

vector<point> half_plane_intersection(vector<line> l) {
    ranges::sort(l, {}, &line::angle);
    int n = l.size(), first = 0, last = 0;
    vector<point> p(n);
    vector<line> q(n);
    q[0] = l[0];
    for (int i = 1; i < n; ++i) {
        while (first < last && !on_left(l[i], p[last - 1]))
            --last;
        while (first < last && !on_left(l[i], p[first]))
            ++first;
        q[++last] = l[i];
        // parallel: keep the inner one
        ld c = cross(q[last].v, q[last - 1].v);
        if (fabsl(c) <= eps) {
            --last;
            if (on_left(q[last], l[i].p)) q[last] = l[i];
        }
        if (first < last)
            p[last - 1] =
                line_intersection(q[last - 1], q[last]);
    }
    while (first < last && !on_left(q[first], p[last - 1]))
        --last;
    if (last - first <= 1) return {};
    p[last] = line_intersection(q[last], q[first]);
    return vector(p.begin() + first, p.begin() + last + 1);
}
