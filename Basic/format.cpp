#include <format>

template<class... T>
void println(format_string<T...> fmt, T&&... args) {
    cout << format(fmt, forward<T>(args)...) << '\n';
}

void format_examples() {
    format("{} + {} = {}", 2, 3, 5); // "2 + 3 = 5"
    format("{1} {0}", "a", "b");     // "b a"
    double x = 3.1415926;
    format("{:.3f}", x);  // "3.142"：小數點後 3 位
    format("{:.3}", x);   // "3.14"：3 位有效數字
    format("{:8.2f}", x); // 寬度 8、小數 2 位
    format("{:<8}", "hi"); // 靠左
    format("{:^8}", "hi"); // 置中
    format("{:>8}", "hi"); // 靠右
    format("{:08}", 42);   // "00000042"
    format("{:+}", 42);    // "+42"
    format("{:#x}", 255);  // "0xff"
    format("{{{}}}", 42);  // "{42}"
    println("answer = {}", 42);
    println("pi = {:.6f}", numbers::pi);
}

// 依分隔字元切開，略過空段（連續空白也 OK），不複製字串，
// 比 stringstream 快；回傳的 view 指向 s，s 不能先被釋放
vector<string_view> split(string_view s, char d = ' ') {
    vector<string_view> res;
    for (auto w : s | views::split(d))
        if (!w.empty())
            res.emplace_back(w.begin(), w.end());
    return res;
}
// 轉數字：from_chars(w.data(), w.data() + w.size(), x);

// 去頭尾空白，全空白回傳 ""
string_view trim(string_view s) {
    auto l = s.find_first_not_of(" \t\r\n");
    if (l == s.npos) return {};
    auto r = s.find_last_not_of(" \t\r\n");
    return s.substr(l, r - l + 1);
}

void ranges_examples(string s, vector<string> ws,
                     vector<pii> ps) {
    erase(s, ' '); // 刪掉所有空白
    erase_if(s, [](char c) { return ispunct(c); });
    ranges::transform(s, s.begin(), ::tolower); // 轉小寫
    s.starts_with("ab"), s.ends_with("yz"); // 前後綴
    ranges::all_of(s, ::isdigit);         // 全是數字
    ranges::equal(s, s | views::reverse); // 回文
    views::iota(0, 4) | views::reverse;   // 3 2 1 0
    auto j = ws | views::join; // 串接 vector<string>
    string all(j.begin(), j.end());
    ranges::sort(ps, {}, &pii::second); // 依 second 排序
    ranges::max(ps, {}, &pii::first);   // 依 first 取最大
    ranges::max_element(ws, {}, &string::size); // 最長
    auto [mn, mx] = ranges::minmax(vector{5, 2, 9});
    // map：for (auto &k : m | views::keys)，values 同理
}

// take / drop：O(1) 建立、不複製；
// 對 view 排序、反轉會直接改到原陣列
void take_drop_examples(vector<int> v, int l, int r,
                        int k, string s) {
    auto sub = v | views::drop(l) | views::take(r - l);
    ranges::sort(sub);   // 只排 [l, r)
    ranges::max(sub);    // [l, r) 最大值
    accumulate(sub.begin(), sub.end(), 0); // [l, r) 總和
    ranges::reverse(v | views::take(k)); // 反轉前 k 個
    for (int x : v | views::drop(1)) {}  // 跳過第一個
    v | views::reverse | views::take(2); // 最後 2 個，倒序
    v | views::take_while([](int x) { return x < 9; });
    s | views::drop_while(::isspace);    // 去開頭空白
}

void more_examples(ll hi, auto ok, vector<int> v,
                   vector<pii> ps, vector<array<ll, 3>> e) {
    // 二分答案：第一個 ok(x) 為真的 x（ok 為 F..F T..T）
    auto bad = [&](ll x) { return !ok(x); };
    ll ans = *ranges::partition_point(views::iota(0LL, hi), bad);
    ranges::max(e | views::elements<2>); // 第 2 欄最大
    ranges::lower_bound(ps, 3, {}, &pii::first); // 依 first
    ranges::sort(v); // 排序去重
    v.erase(ranges::unique(v).begin(), v.end());
    v | views::filter([](int x) { return x % 2; })
      | views::transform([](int x) { return x * x; });
    string s = "abc";
    do {} while (ranges::next_permutation(s).found);
    auto small = [](int i) { return i * i <= 20; };
    for (int i : views::iota(1) | views::take_while(small)) {}
    for (int x : views::istream<int>(cin) | views::take(3)) {}
}
