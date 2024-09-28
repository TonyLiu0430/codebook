const Double EPS = 1e-9;

Double cross(Point p1, Point p2, Point q1) {
	return (p2.x - p1.x) * (q1.y - p1.y) - (p2.y - p1.y) * (q1.x - p1.x);
}

Point interPnt(Point p1, Point p2, Point q1, Point q2, bool &res){
	Double f1 = cross(p2, q1, p1);
	Double f2 = -cross(p2, q2, p1);
	Double f = (f1 + f2);

	if(fabs(f) < EPS) {
		res = false;
		return {};
    }

	res = true;
	return (f2 / f) * q1 + (f1 / f) * q2;
}
