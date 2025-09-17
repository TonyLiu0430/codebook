/* nums 長度 N ;; query 長度為 M */
/* O(N * sqrt(M))*/

struct Query {
    int l, r, id;
};

void add(int pos) {
    /*更新狀態*/
    /*將pos所在的移入集合*/
}

void del(int pos) {
    /*更新狀態*/
    /*將pos所在的移出集合*/
}

int bsz = n / sqrt(m); /*分塊大小 block size*/
sort(query.begin(), query.end(), [bsz](const Query &a, const Query &b){
    if(a.l / bsz != b.l / bsz) {
        return a.l < b.l;
    }
    return (a.l / bsz) & 1 ? a.r < b.r : a.r > b.r;
});

int l = 1;
int r = 0;

vector<pair<int, int>> res(m);

for(int i = 0; i < query.size(); i++ ) {
    auto &q = query[i];
    /*順序不能換*/
    while (l > q.l) add(--l);
    while (r < q.r) add(++r);
    while (l < q.l) del(l++);
    while (r > q.r) del(r--);
    res[q.id] = /* 根據當前狀態求解 */
}
