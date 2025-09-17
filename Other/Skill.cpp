//pbds tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr;

tree::find_by_order(k) // O(logN) 取得第k大的元素
tree::order_of_key(ele) // O(logN) 得到ele是tree中第幾大(有幾個元素小於ele)

//pbds pair priority_queue
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;

priority_queue<int, less<int>, pairing_heap_tag> pq;
auto it = pq.push(x); 
// type of it = priority_queue<int, less<int>, pairing_heap_tag>::point_iterator
pq.pop();
pq.top();
pq.join(b);
pq.empty();
pq.size(); 
pq.modify(it,6);    // O(logN)
pq.erase(it);

//builtin functions
__builtin_popcount(x);  // 1的個數
__builtin_popcountll(x); // for long long
__builtin_clz(x);        // 前導0的個數
__builtin_ctz(x);        // 後導0的個數
__builtin_parity(x);     // 奇偶性

//溢位檢查
ret = __builtin_add_overflow(a, b, &res) // if ret = 1 a+b 溢位
ret = __builtin_sub_overflow(a, b, &res) // if ret = 1 a-b 溢位
ret = __builtin_mul_overflow(a, b, &res) // if ret = 1 a*b 溢位
ret = __builtin_add_overflow_p(a, b, 0LL) // if ret = 1 溢位 第三個參數是判斷的類型

//vector SIMD
typedef int v4si __attribute__ ((vector_size(4 * sizeof(int))));

//大質數表
{1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000123, 1000000321};


//mt19937
#include <random>
#include <chrono>

int getRendom(int l, int r) {
    static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}

//sorted vector 去重
vec.erase(unique(vec.begin(), vec.end()), vec.end());

//std::valarray
valarray<int> a(初始值, 數量);
valarray<int> a(10);
valarray<int> b(10);
valarray<int> c = a + b;
valarray<int> d = a * b;
valarray<int> e = a + 10;
valarray<int> f = a * 10;
valarray<int> g = a.cshift(1); //循環左移
valarray<bool> equal = a == b;
int sum = a.sum();
int max = a.max();
int min = a.min();
std::valarray<int> g = a.apply([](int x) { return x * x; });

//regex  ***very slow***
#include <regex>
using namespace std;
bool res = regex_match("abc", regex("a.c"));
bool res = regex_match("abc", regex("A.c", regex::icase)); //忽略大小寫
