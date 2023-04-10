/*# [NOIP2008 普及组] 传球游戏
## 题目描述
上体育课的时候，小蛮的老师经常带着同学们一起做游戏。这次，老师带着同学们一起做传球游戏。
  游戏规则是这样的：n个同学站成一个圆圈，其中的一个同学手里拿着一个球，当老师吹哨子时开始传球，每个同学可以把
球传给自己左右的两个同学中的一个（左右任意），当老师再次吹哨子时，传球停止，此时，拿着球没有传出去的那个同学
就是败者，要给大家表演一个节目。
  聪明的小蛮提出一个有趣的问题：有多少种不同的传球方法可以使得从小蛮手里开始传的球，传了m次以后，又回到小蛮手
里。两种传球方法被视作不同的方法，当且仅当这两种方法中，接到球的同学按接球顺序组成的序列是不同的。比如有三个
同学1号、2号、3号，并假设小蛮为1号，球传了3次回到小蛮手里的方式有1->2->3->1和1->3->2->1，共2种。
## 输入格式
一行，有两个用空格隔开的整数n,m(3 <= n <= 30,1 <= m <= 30)。
## 输出格式
1个整数，表示符合题意的方法数。
## 样例 #1
### 样例输入 #1
3 3
### 样例输出 #1
2
## 提示
40%的数据满足：3 <= n <= 30,1 <= m <= 20
100%的数据满足：3 <= n <= 30,1 <= m <= 30
2008普及组第三题*/
#include <iostream>
using namespace  std;
struct node
{
    int num;
    node* front;
    node* behind;
    node(int n):num(n){}
    node():num(0){}
};
class queue
{
  private:
  node* head;
  int n;
  public:
  queue(int n)
  {
    this->n=n;
    node* h=new node(1);
    head=h;
    node* tmp=head;
    for(int i=2;i<n;i++)
    {
      node* p=new node(i);
      tmp->behind=p;
      p->front=tmp;
      tmp=p;
    }
    node* p=new node(n);
    tmp->behind=p;
    p->front=tmp;
    p->behind=head;
    head->front=p;
  }
  int sendBall(int m,node* p)
  {
    int count=0;
    if(m==0)
    {
      if(p==head)
      {
        return 1;
      }else 
      {
        return 0;
      }
    }
    m--;
    node* tmp=new node();
    tmp=p->behind;
    count=count+sendBall(m,tmp);
    tmp=p->front;;
    count=count+sendBall(m,tmp);
    return count;
  }
  node* getHead()
  {
    return head;
  }
};
int main()
{
    
    /*queue q(n);
    cout<<q.sendBall(m,q.getHead());*/
    int f[31][31],i,j,m,n;
    cin>>n>>m;
	f[0][1]=1;
	for(int i=1; i<=m; i++)
		for(int j=1; j<=n; j++)
			if(j==1)
				f[i][j]=f[i-1][n]+f[i-1][2];
			else if(j==n)
				f[i][j]=f[i-1][1]+f[i-1][n-1];
			else
				f[i][j]=f[i-1][j-1]+f[i-1][j+1];
	cout<<f[m][1]<<endl;
	return 0;
}