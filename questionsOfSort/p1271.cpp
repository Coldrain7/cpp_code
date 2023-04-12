/*# 【深基9.例1】选举学生会
## 题目描述
学校正在选举学生会成员，有 $n(n\le 999)$ 名候选人，每名候选人编号分别从 1 到 $n$，现在收集到
了 $m(m<=2000000)$ 张选票，每张选票都写了一个候选人编号。现在想把这些堆积如山的选票按照投票数
字从小到大排序。
## 输入格式
输入 $n$ 和 $m$ 以及 $m$ 个选票上的数字。
## 输出格式
求出排序后的选票编号。
## 样例 #1
### 样例输入 #1
5 10
2 5 2 2 5 2 2 2 1 2
### 样例输出 #1
1 2 2 2 2 2 2 2 5 5
```*/
#include <iostream>
#include <cstring>
using namespace std;
void countSort(int* arr,int length,int range){
    int* count=new int[range];
    memset(count,0,range*sizeof(int));
    for(int i=0;i<length;i++){
        count[arr[i]-1]++;
    }
    int j=0;
    for(int i=0;i<range;i++){
        while(count[i]>0){
            arr[j]=1+i;
            count[i]--;
            j++;
        }
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    int* vote=new int [m];
    for(int i=0;i<m;i++){
        cin>>vote[i];
    }
    countSort(vote,m,n);
    for(int i=0;i<m;i++){
        cout<<vote[i]<<" ";
    }
    return 0;
}