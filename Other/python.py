#!/usr/bin/env python3
from collections import deque
import sys


def ints():
    return map(int, input().split())


def all_ints():
    return list(map(int, sys.stdin.buffer.read().split()))


def lcs(a, b):
    dp = [0] * (len(b) + 1)
    for x in a:
        prev = 0
        for j, y in enumerate(b, 1):
            old = dp[j]
            if x == y:
                dp[j] = prev + 1
            else:
                dp[j] = max(dp[j], dp[j - 1])
            prev = old
    return dp[-1]


# stack: append, pop, stack[-1]
# queue = deque(); append, popleft, queue[0]
# sorted unique values: sorted(set(values))
