// Andrew 單調鏈求凸包，O(n log n)，回傳逆時針頂點、不含
// 共線點。
// needs point, cross and eps from 2Dpoint.cpp
vector<point> convex_hull(vector<point> p) {
    ranges::sort(p, [](point a, point b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    });
    auto same = [](point a, point b) {
        return norm2(a - b) <= eps * eps;
    };
    p.erase(ranges::unique(p, same).begin(), p.end());
    if (p.size() <= 1) return p;

    vector<point> h;
    for (int pass = 0; pass < 2; ++pass) {
        size_t base = h.size();
        for (point q : p) {
            while (h.size() >= base + 2 &&
                   cross(h.back() - h.end()[-2],
                         q - h.back()) <= eps)
                h.pop_back();
            h.push_back(q);
        }
        h.pop_back();
        ranges::reverse(p);
    }
    return h; // ccw; first point is not repeated
}
