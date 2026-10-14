// needs 2Dpoint.cpp; a, b, c must not be collinear
point circumcentre(point a, point b, point c) {
    point u = b - a, v = c - a;
    ld d = 2 * cross(u, v);
    point o{v.y * norm2(u) - u.y * norm2(v),
            u.x * norm2(v) - v.x * norm2(u)};
    return a + o * (1 / d);
}
