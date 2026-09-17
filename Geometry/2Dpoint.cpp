using ld = long double;
const ld eps = 1e-12L;

struct point {
    ld x = 0, y = 0;
    point() = default;
    point(ld x, ld y) : x(x), y(y) {}
    point operator+(point p) const { return {x + p.x, y + p.y}; }
    point operator-(point p) const { return {x - p.x, y - p.y}; }
    point operator*(ld k) const { return {x * k, y * k}; }
    bool operator<(point p) const { return tie(x, y) < tie(p.x, p.y); }
};

ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ld cross(point a, point b) { return a.x * b.y - a.y * b.x; }
ld norm2(point p) { return dot(p, p); }
ld norm(point p) { return sqrtl(norm2(p)); }
