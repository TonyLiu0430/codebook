using type = long long;
const type EPS = 0 /*1e-9*/;
struct Point { type x, y; };

inline type cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool overlap(type a, type b, type c, type d) {
    if(a > b) swap(a,b); if(c > d) swap(c,d);
    return max(a,c) <= min(b,d) + EPS;
}

bool equal_zero(type x) {
	return abs(x) <= EPS;
}
bool sgn(type x) {
	return (x > EPS) - (x < -EPS);
}

#define CROSS(i,j,k) cross(p[i],p[j],p[k])

#define CHECK_COLLINEAR(i,j,k) (equal_zero(CROSS(i,j,k)) && overlap(p[i].x,p[j].x,p[k].x,p[k].x) && overlap(p[i].y,p[j].y,p[k].y,p[k].y))

bool intersect(const vector<Point> &p){
    type d[4]; 
    for(int i=0;i<4;i++){
        if(i<2) d[i] = CROSS(0,1,i+2);
        else    d[i] = CROSS(2,3,i-2);
    }
    for(int i=0;i<4;i++)
	/**/if(CHECK_COLLINEAR(i<2?0:2,i<2?1:3,i<2?i+2:i-2)) 
		/**/return true;
	return sgn(d[0]) != sgn(d[1]) && sgn(d[2]) != sgn(d[3]);
}

// 求交點 不處理共線重疊
pair<long double,long double> intersection(const vector<Point> &p){
    long double A1 = p[1].y - p[0].y, B1 = p[0].x - p[1].x, C1 = A1*p[0].x+B1*p[0].y;
    long double A2 = p[3].y - p[2].y, B2 = p[2].x - p[3].x, C2 = A2*p[2].x+B2*p[2].y;
    long double det = A1*B2 - A2*B1;
    return {(C1*B2-C2*B1)/det,(A1*C2-A2*C1)/det};
}