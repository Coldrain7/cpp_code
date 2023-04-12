/*# 【模板】快速排序
## 题目描述
利用快速排序算法将读入的  N  个数从小到大排序后输出。
快速排序是信息学竞赛的必备算法之一。对于快速排序不是很了解的同学可以自行上网查询相关资料，
掌握后独立完成。（C++ 选手请不要试图使用 `STL`，虽然你可以使用 `sort` 一遍过，但是你并
没有掌握快速排序算法的精髓。）
## 输入格式
第  1  行为一个正整数  N ，第  2  行包含  N  个空格隔开的正整数  a_i ，为你需要进行排序的数，
数据保证了  a_i  不超过  10^9 。
## 输出格式
将给定的  N  个数从小到大输出，数之间空格隔开，行末换行且无空格。
## 样例 #1
### 样例输入 #1
5
4 2 4 5 1
### 样例输出 #1
1 2 4 4 5
## 提示
对于  20\%  的数据，有  N\leq 10^3 ；
对于  100\%  的数据，有  N\leq 10^5 。*/
#include <iostream>
using namespace std;
void InsertSort(int* arr, int size){//直接插入排序
	for (int i = 0; i < size - 1; i++){
		//单趟插入排序
		//基本思想：[0,end]区间值为有序
		int end = i;
		int tmp = arr[end + 1];
		while (end >= 0){
			if (arr[end]>tmp){//前一个数更大，即arr[end]>arr[end+1]
				arr[end + 1] = arr[end];
				end--;
			}else{//如果后一个数arr[end+1]更大说明已经有序，可直接跳出循环赋值
				break;//在这里break出去再去赋值tmp是为了防止最后一次end = -1进不来赋值
			}
		}
		arr[end + 1] = tmp;
	}
}
void quickSort(int*arr, int begin,int end){
    if(begin>=end){
        return;
    }
    if(end-begin>10){
    int mid=(begin+end)/2;
    if(arr[begin]>arr[mid]){
        if(arr[begin]>arr[end]){
            if(arr[end]>arr[mid]){
                swap(arr[end],arr[begin]);
            }else{
                swap(arr[mid],arr[begin]);
            }
        }
    }else {
        if(arr[mid]>arr[end]){
            if(arr[end]>arr[begin]){
                swap(arr[begin],arr[end]);
            }
        }else{
            swap(arr[begin],arr[mid]);
        }
    }
    int key=begin;
    int right=end;
    while(begin<end){
        while(arr[end]>=arr[key]&&end>begin){//end大于等于key,end--直到小于key
            end--;
        }
        while(arr[begin]<=arr[key]&&end>begin){//begin小于等于key,begin++直到大于key
            begin++;
        }
        swap(arr[begin],arr[end]);
    }
    swap(arr[key],arr[begin]);
    quickSort(arr,key,begin-1);
    quickSort(arr,begin+1,right);
    }else {
        InsertSort(arr+begin,end-begin+1);
    }
    
}

void insertSort(int a[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
        for (int j = i; j > 0 && a[j] < a[j-1]; j--)
            swap(a[j], a[j-1]);
}

void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    if (right - left + 1 < 10)
    {
        insertSort(a, left, right);
        return;
    }
    int i = left, j = right, k, flag = 0, pivot = rand() % (right - left + 1) + left;
    swap(a[left], a[pivot]);
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
        {
            if (a[j] == a[left])
            {
                for (k = j-1; k > i; k--)
                    if (a[k] != a[j])
                    {
                        swap(a[k], a[j]);
                        break;
                    }
                if (k == i)
                {
                    if (a[left] >= a[i])
                        swap(a[left], a[i]);
                    else
                    {
                        swap(a[i], a[j]);
                        swap(a[left], a[i-1]);
                        i--;
                        j--;
                    }
                    flag = 1;
                    break;
                }
                else continue;
            }
            j--;
        }
        if (flag) break;
        while (i < j && a[i] <= a[left])
        {
            if (a[i] == a[left] && i != left)
            {
                for (k = i+1; k < j; k++)
                {
                    if (a[k] != a[i])
                    {
                        swap(a[k], a[i]);
                        break;
                    }
                }
                if (k == j)
                {
                    swap(a[left], a[j]);
                    flag = 1;
                    break;
                }
                else continue;
            }
            i++;
        }
        if (flag) break;
        swap(a[i], (i == j) ? a[left] : a[j]);
    }
    quickSort(a, left, i-1);
    quickSort(a, j+1, right);
}
int main(){
    int n;
    cin>>n;
    int* m=new int[n];
    for(int i=0;i<n;i++){
        cin>>m[i];
    }
    quickSort(m,0,n-1);
    for(int i=0;i<n;i++){
        cout<<m[i]<<" ";
    }
    return 0;
}