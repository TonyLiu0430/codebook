// count: -1 identical circles; otherwise number of points
struct circle_hit {
    int count;
    vector<point> p;
};

circle_hit circle_intersections(point a, ld r, point b, ld s) {
    point d = b - a;
    ld d2 = norm2(d), len = sqrtl(d2);
    if (len <= eps && fabsl(r - s) <= eps) return {-1, {}};
    if (len <= eps || len > r + s + eps || len < fabsl(r - s) - eps)
        return {0, {}};

    ld x = (d2 + r * r - s * s) / (2 * len);
    ld h2 = max<ld>(0, r * r - x * x);
    point mid = a + d * (x / len);
    if (h2 <= eps) return {1, {mid}};
    point off{-d.y * sqrtl(h2) / len, d.x * sqrtl(h2) / len};
    return {2, {mid + off, mid - off}};
}
