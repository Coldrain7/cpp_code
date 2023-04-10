/*# [NOIP2002 普及组] 过河卒
## 题目描述
棋盘上 A 点有一个过河卒，需要走到目标 B 点。卒行走的规则：可以向下、或者向右。同时在棋盘上 C 点有
一个对方的马，该马所在的点和所有跳跃一步可达的点称为对方马的控制点。因此称之为“马拦过河卒”。
棋盘用坐标表示，A 点 (0, 0)、B 点 (n, m)，同样马的位置坐标是需要给出的。
![](https://cdn.luogu.com.cn/upload/image_hosting/vg6k477j.png)
现在要求你计算出卒从 A 点能够到达 B 点的路径的条数，假设马的位置是固定不动的，并不是卒走一步马走一步。
## 输入格式
一行四个正整数，分别表示 B 点坐标和马的坐标。
## 输出格式
一个整数，表示所有的路径条数。
## 样例 #1
### 样例输入 #1
6 6 3 3
### 样例输出 #1
6
## 提示
对于 100 \% 的数据，1 <= n, m <= 20，0 <= 马的坐标 <= 20。
**【题目来源】**
NOIP 2002 普及组第四题*/
#include <iostream>
using namespace std;
void eliminateHorsePoint(long long map[21][21],int hx,int hy)
{
    map[hx][hy]=1;
    int tx,ty;
    tx=hx-2;
    if(tx>=0)
    {
        ty=hy-1;
        if(ty>=0) map[tx][ty]=1;
        ty=hy+1;
        if(ty>=0) map[tx][ty]=1;
    }
    tx=hx-1;
    if(tx>=0)
    {
        ty=hy-2;
        if(ty>=0) map[tx][ty]=1;
        ty=hy+2;
        if(ty>=0) map[tx][ty]=1;
    }
    tx=hx+2;
    if(tx>=0)
    {
        ty=hy-1;
        if(ty>=0) map[tx][ty]=1;
        ty=hy+1;
        if(ty>=0) map[tx][ty]=1;
    }
    tx=hx+1;
    if(tx>=0)
    {
        ty=hy-2;
        if(ty>=0) map[tx][ty]=1;
        ty=hy+2;
        if(ty>=0) map[tx][ty]=1;
    }
}
//递归思路，但是效率不高
void findPath(int ax,int ay,int n,int m,bool map[21][21],int &ans)
{
    if(ax>n||ay>m)
    {
        return;
    }
    if(ax==n&&ay==m)
    {
        ans++;
        return;
    }
    if(ax<n&&!(map[ax+1][ay]^map[ax][ay]))
    {
        findPath(ax+1,ay,n,m,map,ans);
    }
    if(ay<m&&!(map[ax][ay+1]^map[ax][ay]))
    {
        findPath(ax,ay+1,n,m,map,ans);
    }

}
void findPath(int ax,int ay,int n,int m,long long map[21][21])
{
    map[0][0]=1;
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(i+j==0)
            {
                continue;
            }else if(map[i][j]==0||i+j==0)//非控制点
            {
                if(i-1<0)//在边界
                {
                    map[i][j]=map[i][j-1];
                }else if(j-1<0)
                {
                    map[i][j]=map[i-1][j];
                }else//不在边界
                {
                    map[i][j]=map[i-1][j]+map[i][j-1];
                }
            }else
            {
                map[i][j]=0;
            }
        }
    }
 //   return map[n][m];
}
int main()
{
    int horsex,horsey,n,m;
    int ans=0;
    long long map[21][21]={0};
    cin>>n>>m>>horsex>>horsey;
    eliminateHorsePoint(map,horsex,horsey);
    //cout<<findPath(0,0,n,m,map)<<endl;
    findPath(0,0,n,m,map);
    cout<<map[n][m];
    return 0;
}

