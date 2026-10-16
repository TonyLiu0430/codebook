import sys
from bisect import bisect_left,bisect_right
from collections import Counter,defaultdict,deque
from functools import cache
from heapq import heappop,heappush
from itertools import accumulate,combinations
from itertools import permutations,product
from math import comb,factorial,gcd,isqrt,lcm,perm
input=sys.stdin.buffer.readline
sys.setrecursionlimit(1<<25)
n=int(input()); a=list(map(int,input().split()))
a=list(map(int,sys.stdin.buffer.read().split()))
print(*a); print(*a,sep="\n"); "".join(map(str,a))
combinations(a,k); permutations(a); product(a,repeat=k)
sorted(a,key=lambda x:(x[0],-x[1]))
b=sorted(set(a)); rk={x:i for i,x in enumerate(b)}
bisect_left(a,x); bisect_right(a,x)
st=[]; st.append(x); x=st.pop()
q=deque(); q.append(x); x=q.popleft()
h=[];heappush(h,x);x=heappop(h);heappush(h,-x);x=-heappop(h)
cnt=Counter(a); g=defaultdict(list)
pre=[0]+list(accumulate(a)); pre[r]-pre[l]
gcd(a,b);lcm(a,b);isqrt(n);comb(n,k);perm(n,k);factorial(n)
pow(a,e,mod);pow(a,-1,mod);x.bit_count();x.bit_length();x&-x
dp=[[0]*m for _ in range(n)]
@cache
def f(state): ...
