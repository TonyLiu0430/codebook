using ld = long double;
const ld eps = 1e-12L;

struct point {
    ld x = 0, y = 0;
};

point operator+(point a, point b) { return {a.x + b.x, a.y + b.y}; }
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
point operator*(point p, ld k) { return {p.x * k, p.y * k}; }
ld dot(point a, point b) { return a.x * b.x + a.y * b.y; }
ld cross(point a, point b) { return a.x * b.y - a.y * b.x; }
ld norm2(point p) { return dot(p, p); }
ld norm(point p) { return sqrtl(norm2(p)); }
