#!/bin/bash
# ./stress.sh 待測解 暴力解 測資（省略 .cpp，預設 a b gen）
# 先 chmod +x stress.sh 或用 bash 跑；浮點／多解改 checker
a=${1:-a} b=${2:-b} gen=${3:-gen}
msvc="g++ -O2 -std=gnu++20"
$msvc -o $a $a.cpp && $msvc -o $b $b.cpp &&
$msvc -o $gen $gen.cpp || exit 1
for ((i = 1; ; ++i)); do
    ./$gen $i > in
    ./$a < in > out1
    ./$b < in > out2
    if ! cmp -s out1 out2; then
        echo "WA on seed $i"; cat in; break
    fi
done
