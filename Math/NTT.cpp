/*預處理 lim lim >= lenA + lenB - 1*/
while (lim < (lenA + lenB - 1)) lim <<= 1;
/*預處理 r*/
int r[N];
for (i = 0; i < lim; ++i) r[i] = (i & 1) * (lim >> 1) + (r[i >> 1] >> 1);
///////////////////////////////////////
constexpr int P = 998244353; 
const int G = 3;
/*998244353	3
1004535809	3
469762049	3
167772161	3
754974721	11*/
// lim 一定要是 2 的冪次   opt == -1 => inverse ntt
// x.size() == lim
void ntt(vector<int> &x, int lim, int opt) { 
  int i, j, k, m, gn, g, tmp;
  for (i = 0; i < lim; ++i)
    if (r[i] < i) swap(x[i], x[r[i]]);
  for (m = 2; m <= lim; m <<= 1) {
    k = m >> 1;
    gn = qpow(G, (P - 1) / m);
    for (i = 0; i < lim; i += m) {
      g = 1;
      for (j = 0; j < k; ++j, g = 1ll * g * gn % P) {
        tmp = 1ll * x[i + j + k] * g % P;
        x[i + j + k] = (x[i + j] - tmp + P) % P;
        x[i + j] = (x[i + j] + tmp) % P;
      }
    }
  }
  if (opt == -1) {
    reverse(x + 1, x + lim);
    int inv = qpow(lim, P - 2);
    for (i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % P;
  }
}