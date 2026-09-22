#include <format>

template<class... t>
void println(format_string<t...> fmt, t&&... args) {
    cout << format(fmt, forward<t>(args)...) << '\n';
}

/*
format("{} + {} = {}", 2, 3, 5); // "2 + 3 = 5"
format("{1} {0}", "a", "b");     // "b a"

double x = 3.1415926;
format("{:.3f}", x);  // "3.142": fixed, 3 digits after decimal point
format("{:.3}", x);   // "3.14": 3 significant digits
format("{:8.2f}", x); // width 8, fixed 2 digits

format("{:<8}", "hi"); // left align
format("{:^8}", "hi"); // center
format("{:>8}", "hi"); // right align
format("{:08}", 42);   // "00000042"
format("{:+}", 42);    // "+42"
format("{:#x}", 255);  // "0xff"
format("{{{}}}", 42);  // "{42}"

println("answer = {}", 42);
println("pi = {:.6f}", numbers::pi);
*/
