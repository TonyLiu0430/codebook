新的方法介紹
下面我們介紹一個新的方法－Matrix-Tree定理(Kirchhoff矩陣-樹定理)。

Matrix-Tree定理是解決生成樹數問題最有力的武器之一。它首先於1847年被Kirchhoff證明。在介紹定理之前，我們先先明確幾個概念：
1.G的度數矩陣D[G]是一個n*n的矩陣，並且滿足：當i≠j時,dij=0；當i=j時，dij等於vi的度數。
2.G的鄰接矩陣A[G]也是一個n*n的矩陣， 且滿足：若vi、vj之間有邊直接相連，則aij=1，否則為0。
我們定義G的Kirchhoff矩陣(也稱為拉普拉斯算子)C[G]為C[G]=D[G]-A[G]，
則Matrix-Tree定理可以描述為：G的所有不同的生成樹的個數等於其Kirchhoff矩陣C[G]任何一個n-1階主子式的行列式的絕對值。
所謂n-1階主子式，就是對於r(1≤r≤n)，將C[G]的第r行、第r列同時去掉後所得到的新矩陣，以Cr[G]表示。


生成樹計數
演算法步驟：
1、 建構拉普拉斯矩陣
 Matrix[i][j] =
degree(i) , i==j
 -1，i-j有邊
 0，其他情況
2、 去掉第r行，第r列（r任意）
3、 計算矩陣的行列式

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;
const double eps = 1e-8;
const int MAXN = 110;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
double b[MAXN][MAXN];
double det(double a[][MAXN],int n)
{
    int i, j, k, sign = 0;
    double ret = 1;
    for(i = 0;i < n;i++)
    for(j = 0;j < n;j++) b[i][j] = a[i][j];
    for(i = 0;i < n;i++)
    {
        if(sgn(b[i][i]) == 0)
        {
            for(j = i + 1; j < n;j++)
            if(sgn(b[j][i]) != 0) break;
            if(j == n)return 0;
            for(k = i;k < n;k++) swap(b[i][k],b[j][k]);
            sign++;
        }
        ret *= b[i][i];
        for(k = i + 1;k < n;k++) b[i][k]/=b[i][i];
        for(j = i+1;j < n;j++)
        for(k = i+1;k < n;k++) b[j][k] -= b[j][i]*b[i][k];
    }
    if(sign & 1)ret = -ret;
    return ret;
}
double a[MAXN][MAXN];
int g[MAXN][MAXN];
int main()
{
    int T;
    int n,m;
    int u,v;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        memset(g,0,sizeof(g));
        while(m--)
        {
            scanf("%d%d",&u,&v);
            u--;v--;
            g[u][v] = g[v][u] = 1;
        }
        memset(a,0,sizeof(a));
        for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
        if(i != j && g[i][j])
        {
            a[i][i]++;
            a[i][j] = -1;
        }
        double ans = det(a,n-1);
        printf("%.0lf\n",ans);
    }
    return 0;
}
