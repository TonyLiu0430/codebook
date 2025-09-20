struct Point {
    double x, y;
}; 

Point operator*(double a, Point p) {
    return {a * p.x, a * p.y};
}

Point operator+(Point a, Point b) {
    return {a.x + b.x, a.y + b.y};
}

const double EPS = 1e-9;

double cross(Point p1, Point p2, Point q1) {
	return (p2.x - p1.x) * (q1.y - p1.y) - (p2.y - p1.y) * (q1.x - p1.x);
}

template<class T>
bool inter(T a, T b, T c) {
    if(b < a) swap(a, b);
	return c >= a && c <= b;
}

bool is_in(Point p1, Point p2, Point q) { // 判斷 q 是否在 線段 p1 p2 內
	return inter(p1.x, p2.x, q.x) && inter(p1.y, p2.y, q.y);
}

Point interPnt(Point p1, Point p2, Point q1, Point q2, bool &res){
	double f1 = cross(p2, q1, p1);
	double f2 = -cross(p2, q2, p1);
	double f = (f1 + f2);

	if(fabs(f) < EPS) {
		res = false;
		return {};
    }

	Point ip = (f2 / f) * q1 + (f1 / f) * q2; // intersection point
	if(is_in(p1, p2, ip) && is_in(q1, q2, ip)) { // 兩直線交點不用這段
		res = true;
		return ip;
	}
	res = false;
	return {};
}