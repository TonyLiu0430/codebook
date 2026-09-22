// all ranges are [l, r]
struct query {
    int l, r, id;
};

void sort_mo(vector<query> &queries, int n) {
    int block = max(1, int(n / sqrt(max<size_t>(1, queries.size()))));
    ranges::sort(queries, [&](query a, query b) {
        int x = a.l / block, y = b.l / block;
        if (x != y) return x < y;
        return x & 1 ? a.r < b.r : a.r > b.r;
    });
}

/*
start with l=0, r=-1 (empty).
move in this order:
while (l > q.l) add(--l); while (r < q.r) add(++r);
while (l < q.l) remove(l++); while (r > q.r) remove(r--);
*/
