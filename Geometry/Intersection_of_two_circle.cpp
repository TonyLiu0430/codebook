vector<Point> interCircle(Point o1, type r1, Point o2, type r2) {
    type d2 = abs2(o1 - o2);
    type d = sqrt(d2);
    if (d < fabs(r1 - r2) || d > r1 + r2) return {};
    Point u = (o1 + o2) * 0.5 + ((r2*r2 - r1*r1) / (2.0*d2)) * (o1 - o2);
    type A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
    Point v = Point{o1.y - o2.y, -(o1.x - o2.x)} * (A / (2.0*d2));
    return { u + v, u - v };
}