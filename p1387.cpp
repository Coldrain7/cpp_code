/*# 最大正方形
## 题目描述
在一个 $n\times m$ 的只包含 $0$ 和 $1$ 的矩阵里找出一个不包含 $0$ 的最大正方形，输出边长。
## 输入格式
输入文件第一行为两个整数 $n,m(1\leq n,m\leq 100)$，接下来 $n$ 行，每行 $m$ 个数字，用空格隔开，$0$
 或 $1$。
## 输出格式
一个整数，最大正方形的边长。
## 样例 #1
### 样例输入 #1
4 4
0 1 1 1
1 1 1 0
0 1 1 0
1 1 0 1
### 样例输出 #1
2
*/
#include <iostream>
using namespace std;
int main()
{
    bool a[101][101];
    int f[101][101],n,m,ans=0;
    cin>>n>>m;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
        {
            scanf("%d",&a[i][j]);
            if (a[i][j]==1) f[i][j]=min(min(f[i][j-1],f[i-1][j]),f[i-1][j-1])+1;
            ans=max(ans,f[i][j]);//同步更新答案
        }
    cout<<ans;
    return 0;
}
