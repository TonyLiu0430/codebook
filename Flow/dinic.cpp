(a) 有源匯上下界最大流 (Bounded Maxflow)
目標：在滿足所有邊的流量上下界限制的前提下，從源點 s 到匯點 t 的最大流量。
先依照 (b) 的方法建立 可行流 模型。
檢查是否存在可行流（即 max_flow(ss, tt) 是否等於所有流量下界 l 的總和）。如果不可行，則此問題無解。
重要：如果可行，不要重新初始化圖。直接在當前的殘留網路上繼續計算 dinic.max_flow(s, t)。
最終的答案就是步驟 3 中計算出的從 s 到 t 的附加流量。

(b) 有上下界可行流 (Bounded Possible Flow)
目標：檢查是否存在一種流量分配，使得每條邊的流量 f 都滿足其下界 l 和上界 r 的限制 (l ≤ f ≤ r)。
新增兩個節點：超級源點 ss 和超級匯點 tt。
準備一個變數 total_lower_bound 來累加所有下界 l。
對於每一條原始邊 u -> v，其容量為 [l, r]：
dinic.add_edge(u, v, r - l);  (邊的彈性容量)
dinic.add_edge(ss, v, l);     (節點 v 需要 l 的流入)
dinic.add_edge(u, tt, l);     (節點 u 提供 l 的流出)
total_lower_bound += l;
計算 flow = dinic.max_flow(ss, tt)。
如果 flow == total_lower_bound，則表示所有下界需求都被滿足，存在可行流；否則不存在。

(c) 有源匯上下界最小流 (Bounded Minimum Flow)
目標：在滿足所有邊的流量上下界限制的前提下，從源點 s 到匯點 t 的最小流量。
注意：這個問題通常需要透過二分搜尋答案來解決，無法直接用一次最大流求出。
二分搜尋一個流量值 F。
對於每個猜測的 F，建立一個無源匯可行流模型來檢查其可行性：
使用 (b) 的方法建構基本圖。
額外加入一條邊 t -> s，容量為 [F, INF]。這條邊強制要求從 s 到 t 的淨流量至少為 F。
檢查這個新的循環圖是否存在可行流。如果存在，表示流量 F 是可達成的，可以嘗試更小的 F；反之，F 太小了，需要增加。

(e) 最小割 (Minimum Cut)
目標：找出一個邊集，其總容量最小，且移除這些邊後 s 和 t 不再連通。
根據最大流-最小割定理，最小割的值等於最大流的值。先執行 ll min_cut_value = dinic.max_flow(s, t);。
呼叫 vector<bool> side = dinic.get_min_cut_nodes(s); 來取得節點的劃分。
side[i] == true 表示節點 i 屬於源點 s 所在的集合 (S 集合)。
side[i] == false 表示節點 i 屬於匯點 t 所在的集合 (T 集合)。
最小割的邊集就是所有從 S 集合指向 T 集合的原始邊

using ll = long long;
const ll INF = 1e18;

struct Dinic {
    struct Edge {
        int to;
        ll cap;
        int rev; // 反向邊的索引
    };
    vector<vector<Edge>> adj;
    vector<int> level, iter;
    vector<bool> side;
    int n;
    Dinic(int v) : n(v), adj(v), level(v), iter(v) {}
    void add_edge(int u, int v, ll cap) {
        adj[u].push_back({v, cap, (int)adj[v].size()});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& edge : adj[u]) {
                if (edge.cap > 0 && level[edge.to] < 0) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = iter[u]; i < (int)adj[u].size(); ++i) {
            Edge& e = adj[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    adj[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    ll max_flow(int s, int t) {
        ll flow = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            ll f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
    void _find_cut(int u) {
        side[u] = true;
        for(const auto& e : adj[u]) {
            if(e.cap > 0 && !side[e.to]) {
                _find_cut(e.to);
            }
        }
    }
    vector<bool> get_min_cut_nodes(int s) { // 跟 S 同側 true ; 跟 T 同側 false
        fill(side.begin(), side.end(), false);
        _find_cut(s);
        return side;
    }
};
