// Bellman-Ford 單源最短路，可處理負權邊並偵測從源點可達
// 的負環，O(VE)。
using ll = long long;
const ll inf = LLONG_MAX / 4;

struct edge {
    int from, to;
    ll weight;
};
struct bellman_result {
    vector<ll> dist;
    vector<int> parent;
    bool negative_cycle;
};

bellman_result bellman_ford(int n, int source,
                            const vector<edge> &edges) {
    vector<ll> dist(n, inf);
    vector<int> parent(n, -1);
    dist[source] = 0;
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        changed = false;
        for (edge e : edges) {
            if (dist[e.from] == inf) continue;
            auto x = (__int128)dist[e.from] + e.weight;
            ll nd = clamp<__int128>(x, -inf, inf);
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                parent[e.to] = e.from;
                changed = true;
            }
        }
        if (!changed) break;
    }
    // reachable negative cycle iff changed
    return {dist, parent, changed};
}

/*
差分約束：x_v - x_u <= w  ->  edge u -> v, weight w
  x_v - x_u >= w -> v -> u, -w；等式拆成兩條
  x_v <= c / x_v >= c：設 x_0 = 0 當成變數處理
  整數嚴格 x_v - x_u < w -> x_v - x_u <= w - 1
加超級源點 s，s -> 每個變數權重 0，從 s 跑 bellman_ford
有負環 -> 無解；否則 x_v = dist[v] (所有 x <= 0 中最大解)
要最小解：約束反向跑最長路
最小平均環：二分答案 x，邊權改 w - x（實數；或整數權重
  全部乘分母），有負環 <=> 存在平均 < x 的環
找任意負環（不限源點可達）：加超級源點連到每點權重 0
*/
