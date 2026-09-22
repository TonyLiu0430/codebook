// needs point, cross and eps from 2Dpoint.cpp
vector<point> convex_hull(vector<point> p) {
    ranges::sort(p, [](point a, point b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    });
    p.erase(ranges::unique(p, [](point a, point b) {
        return fabsl(a.x - b.x) <= eps && fabsl(a.y - b.y) <= eps;
    }).begin(), p.end());
    if (p.size() <= 1) return p;

    vector<point> h;
    for (int pass = 0; pass < 2; ++pass) {
        size_t base = h.size();
        for (point q : p) {
            while (h.size() >= base + 2 &&
                   cross(h.back() - h[h.size() - 2], q - h.back()) <= eps)
                h.pop_back();
            h.push_back(q);
        }
        h.pop_back();
        ranges::reverse(p);
    }
    return h; // ccw; first point is not repeated
}
