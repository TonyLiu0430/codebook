#ifdef LOCAL // g++ -DLOCAL; open the .svg in a browser
struct svg { // shows [x1,x2] x [y1,y2], y axis points up
    ofstream o;
    string c = "red"; // current color
    double X, Y, k;    // map to [0, 1000] for the browser
    void p(string_view s) { o << s; }
    void p(string_view s, auto v, auto... vs) {
        auto i = s.find('$');
        o << s.substr(0, i) << v;
        p(s.substr(i + 1), vs...);
    }
    double tx(double x) { return (x - X) * k; }
    double ty(double y) { return (Y - y) * k; }
    svg(string f, double x1, double y1, double x2,
        double y2) : o(f), X(x1), Y(y2) {
        k = 1e3 / max(x2 - x1, y2 - y1);
        p("<svg xmlns='http://www.w3.org/2000/svg' "
          "viewBox='-50 -50 $ $'><style>"
          "*{stroke-width:.3%;fill:none}"
          "text{fill:black;text-anchor:middle;"
          "dominant-baseline:central}</style>\n",
          tx(x2) + 100, ty(y1) + 100);
    }
    ~svg() { p("</svg>\n"); }
    void line(double x1, double y1, double x2, double y2) {
        p("<line x1='$' y1='$' x2='$' y2='$' "
          "stroke='$'/>\n",
          tx(x1), ty(y1), tx(x2), ty(y2), c);
    }
    void circle(double x, double y, double r,
                string fill = "none") {
        p("<circle cx='$' cy='$' r='$' stroke='$' style="
          "'fill:$'/>\n", tx(x), ty(y), r * k, c, fill);
    }
    void text(double x, double y, auto s, double size) {
        p("<text x='$' y='$' font-size='$'>$</text>\n",
          tx(x), ty(y), size * k, s);
    }
    // svg(f, -1.2, -1.2, 1.2, 1.2); small ring = head
    void graph(int n, const vector<pair<int, int>> &e) {
        double t = 2 * acos(-1) / n;
        auto x = [&](double i) { return cos(t * i); };
        auto y = [&](double i) { return sin(t * i); };
        for (auto [u, v] : e) {
            line(x(u), y(u), x(v), y(v));
            circle(lerp(x(u), x(v), .85),
                   lerp(y(u), y(v), .85), .02);
        }
        for (int i = 0; i < n; ++i)
            circle(x(i), y(i), .07, "#fff"),
            text(x(i), y(i), i, .08);
    }
};
#else
struct svg {
    string c;
    svg(auto...) {}
    void line(auto...) {}
    void circle(auto...) {}
    void text(auto...) {}
    void graph(auto...) {}
};
#endif
