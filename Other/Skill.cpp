//pbds小抄
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> tr;

//tree::find_by_order(k) O(logN) 取得第k大的元素
//tree::order_of_key(ele) O(logN) 得到ele是tree中第幾大(有幾個元素小於ele)

//builtin functions
// __builtin_popcount(x) 1的個數
// __builtin_popcountll(x) for long long
// __builtin_clz(x) 前導0的個數
// __builtin_ctz(x) 後導0的個數
// __builtin_parity(x) 奇偶性

//溢位檢查
// ret = __builtin_add_overflow(a, b, &res) if ret = 1 a+b 溢位
// ret = __builtin_sub_overflow(a, b, &res) if ret = 1 a-b 溢位
// ret = __builtin_mul_overflow(a, b, &res) if ret = 1 a*b 溢位
// ret = __builtin_add_overflow_p(a, b, 0LL) if ret = 1 溢位 第三個參數是判斷的類型

//vector SIMD
typedef int v4si __attribute__ ((vector_size(4 * sizeof(int))));

//大質數表
{1000000007, 1000000009, 1000000021, 1000000033, 1000000087, 1000000093, 1000000097, 1000000123, 1000000321};

//mt19937
#include <random>
#include <chrono>

int getRendom(int l, int r) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}