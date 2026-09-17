// needs point, cross and eps from 2Dpoint.cpp
vector<point> convex_hull(vector<point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end(), [](point a, point b) {
        return fabsl(a.x - b.x) <= eps && fabsl(a.y - b.y) <= eps;
    }), p.end());
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
        reverse(p.begin(), p.end());
    }
    return h; // ccw; first point is not repeated
}
