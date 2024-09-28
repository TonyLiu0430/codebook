struct node {
    int num{}, w{};
    bool operator < (const node& other)const {
        return w > other.w;
    }
};

vector<int> dijkstra(int root, const vector<vector<node>> &graph) {
    vector<int> d(graph.size(), INT_MAX >> 1), p(graph.size());
    priority_queue<node> pq;
    d[root] = p[root] = 0;
    pq.push({root, d[root]});
    while (!pq.empty()) {
        node tmp = pq.top(); pq.pop();
        for (const node &i : graph[tmp.num]) {
            if (d[i.num] > d[tmp.num] + i.w) {
                d[i.num] = d[tmp.num] + i.w;
                p[i.num] = tmp.num;
                pq.push({i.num, d[tmp.num]});
            }
        }
    }
    return d;
}

