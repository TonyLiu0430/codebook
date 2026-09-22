// all ranges are [l, r]; time = number of applied updates
struct time_query {
    int l, r, time, id;
};

void sort_mo_with_updates(vector<time_query> &queries, int n) {
    int block = max(1, int(pow(max(1, n), 2.0 / 3)));
    ranges::sort(queries, [&](time_query a, time_query b) {
        int al = a.l / block, bl = b.l / block;
        if (al != bl) return al < bl;
        int ar = a.r / block, br = b.r / block;
        if (ar != br) return al & 1 ? ar < br : ar > br;
        return ar & 1 ? a.time < b.time : a.time > b.time;
    });
}

// start with l=0, r=-1, time=0; apply/undo updates while moving time
