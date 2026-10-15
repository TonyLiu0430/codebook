# 對拍：a = 待測解，b = 暴力解，gen = 隨機測資（見下）
# 輸出有浮點數或多解時，把 cmp 換成自己寫的 checker
msvc="g++ -O2 -std=gnu++20"
$msvc -o a a.cpp && $msvc -o b b.cpp &&
$msvc -o gen gen.cpp || exit 1
for ((i = 1; ; ++i)); do
    ./gen $i > in
    ./a < in > out1
    ./b < in > out2
    if ! cmp -s out1 out2; then
        echo "WA on seed $i"; cat in; break
    fi
done
