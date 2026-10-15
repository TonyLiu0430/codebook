# 對拍：a = 待測解，b = 暴力解，gen = 隨機測資（見下）
# 輸出有浮點數或多解時，把 cmp 換成自己寫的 checker
g++ -O2 -o a a.cpp && g++ -O2 -o b b.cpp &&
g++ -O2 -o gen gen.cpp || exit 1
for ((i = 1; ; ++i)); do
    ./gen $i > in
    ./a < in > out1
    ./b < in > out2
    if ! cmp -s out1 out2; then
        echo "WA on seed $i"; cat in; break
    fi
done
