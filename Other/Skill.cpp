#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;

using ordered_set = tree<int, null_type, less<int>, rb_tree_tag,
                         tree_order_statistics_node_update>;
// s.find_by_order(k): iterator to k-th smallest, 0-based
// s.order_of_key(x): number of values strictly smaller than x

using pairing_heap = __gnu_pbds::priority_queue<int, less<int>, pairing_heap_tag>;
// auto it = q.push(x); q.modify(it, y); q.erase(it); q.join(other);

// __builtin_popcount(x), __builtin_popcountll(x)
// __builtin_clz(x), __builtin_ctz(x): x must be nonzero
// __builtin_*_overflow(a, b, &answer)

int random_int(int l, int r) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<int>(l, r)(rng);
}

// sorted unique:
// a.erase(ranges::unique(a).begin(), a.end());
