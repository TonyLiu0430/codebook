#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using __gnu_cxx::rope;
using ordered_set =
    tree<int, null_type, less<int>, rb_tree_tag,
         tree_order_statistics_node_update>;
// s.find_by_order(k)：第 k 小，從 0 開始
// s.order_of_key(x)：嚴格小於 x 的元素個數
using pairing_heap =
    __gnu_pbds::priority_queue<int, less<int>,
                               pairing_heap_tag>;
// auto it=q.push(x);q.modify(it,y);q.erase(it);q.join(q2);
// __builtin_popcount(x), __builtin_popcountll(x)
// __builtin_clz(x), __builtin_ctz(x)：x 不可為 0
// __builtin_*_overflow(a, b, &answer)
vector<rope<char>> ver{rope<char>("abc")};
void edit(int k, int pos, int len) {
    ver.push_back(ver[k]); // O(1) 複製，保留舊版本
    ver.back().insert(pos, "xyz");
    ver.back().replace(pos,'X'); // [] 不能指派
    ver.back().erase(pos,len); // len 是長度；單參數版有坑
    auto sub = ver.back().substr(pos, len);
}
// 排序後去重：
// a.erase(ranges::unique(a).begin(), a.end());
