using i128 = __int128_t;

struct ipoint {
    long long x, y;
};

i128 cross(ipoint a, ipoint b, ipoint c) {
    return (i128(b.x) - a.x) * (i128(c.y) - a.y) -
           (i128(b.y) - a.y) * (i128(c.x) - a.x);
}

int sign(i128 x) { return (x > 0) - (x < 0); }

bool on_segment(ipoint a, ipoint b, ipoint p) {
    return cross(a, b, p) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool segments_intersect(ipoint a, ipoint b, ipoint c, ipoint d) {
    i128 x = cross(a, b, c), y = cross(a, b, d);
    i128 z = cross(c, d, a), w = cross(c, d, b);
    if (!x && on_segment(a, b, c)) return true;
    if (!y && on_segment(a, b, d)) return true;
    if (!z && on_segment(c, d, a)) return true;
    if (!w && on_segment(c, d, b)) return true;
    return sign(x) != sign(y) && sign(z) != sign(w);
}
