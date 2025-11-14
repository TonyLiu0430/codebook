struct Node {
    int val, pri, sz;
    Node *l{}, *r{};

    Node(int v) : val(v), pri(rand()), sz(1) {}
    void update() {
        sz = 1 + (l ? l->sz : 0) + (r ? r->sz : 0);
    }
};

struct Split { 
    Node* l;
    Node* r;
};

int getsz(Node* t) { return t ? t->sz : 0; }
Split split_by_size(Node* t, int k) {
    if (!t) return {nullptr, nullptr};

    int ls = getsz(t->l);
    if (ls >= k) {
        auto sp = split_by_size(t->l, k);
        t->l = sp.r;
        t->update();
        return {sp.l, t};
    } else {
        auto sp = split_by_size(t->r, k - ls - 1);
        t->r = sp.l;
        t->update();
        return {t, sp.r};
    }
}
Split split_by_value(Node* t, int key) {
    if (!t) return {nullptr, nullptr};

    if (t->val <= key) {
        auto sp = split_by_value(t->r, key);
        t->r = sp.l;
        t->update();
        return {t, sp.r};
    } else {
        auto sp = split_by_value(t->l, key);
        t->l = sp.r;
        t->update();
        return {sp.l, t};
    }
}
Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;

    if (a->pri < b->pri) {
        a->r = merge(a->r, b);
        a->update();
        return a;
    } else {
        b->l = merge(a, b->l);
        b->update();
        return b;
    }
}
