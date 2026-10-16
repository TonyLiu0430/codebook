#ifdef LOCAL // g++ -DLOCAL; open the .html in a browser
struct svg { // shows [x1,x2] x [y1,y2], y axis points up
    ofstream o;
    string c = "red"; // 可用：red blue green orange purple black
    double X, Y, k;    // map to [0, 1000] for the browser
    void p(string_view s, auto... x) {
        o << vformat(s, make_format_args(x...));
    }
    double tx(double x) { return (x - X) * k; }
    double ty(double y) { return (Y - y) * k; }
    // path 要以 .html 結尾；畫 graph() 建議 svg(path, -1, -1, 1, 1)
    svg(string path, double x1, double y1, double x2,
        double y2) : o(path), X(x1), Y(y2) {
        k = 1e3 / max(x2 - x1, y2 - y1);
        p("<svg width=1000 viewBox=-50,-50,{},{} stroke-width=.3% "
          "text-anchor=middle dominant-baseline=central>"
          // 不畫 graph() 可刪除此段
          "<marker id=a orient=auto overflow=visible>"
          "<path d=M-14-3l5,3-5,3z "
          "fill=context-stroke /></marker>",
          tx(x2) + 100, ty(y1) + 100);
    }
    void line(double x1, double y1, double x2, double y2) {
        p("<path d=M{},{}L{},{} stroke={} />",
          tx(x1), ty(y1), tx(x2), ty(y2), c);
    }
    void circle(double x, double y, double r,
                string fill = "none") {
        p("<circle cx={} cy={} r={} stroke={} fill={} />",
          tx(x), ty(y), r * k, c, fill);
    }
    void text(double x, double y, auto s, double size) {
        p("<text x={} y={} font-size={}>{}</text>",
          tx(x), ty(y), size * k, s);
    }
    void graph(int n, const vector<pair<int, int>> &e) { // 圖論的圖
        double t = 2 * acos(-1) / n;
        auto x = [&](double i) { return cos(t * i); };
        auto y = [&](double i) { return sin(t * i); };
        p("<g marker-end=url(#a)>");
        for (auto [u, v] : e)
            line(x(u), y(u), x(v), y(v));
        p("</g>");
        for (int i = 0; i < n; ++i)
            circle(x(i), y(i), .07, "#fff"),
            text(x(i), y(i), i, .08);
    }
};
#else
struct svg { string c; svg(auto...) {} void line(auto...) {} void circle(auto...) {} void text(auto...) {} void graph(auto...) {} };
#endif
