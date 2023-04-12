#include <iostream>
#include <cassert>
#include <cstring>
using namespace  std;
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
void insertSort(int a[], int left, int right){
    for (int i = left + 1; i <= right; i++)
        for (int j = i; j > 0 && a[j] < a[j-1]; j--)
            swap(a[j], a[j-1]);
}
void ShellSort(int* arr, int size){//希尔排序
	int gap = size;
	//多次预排+最后一次直接插入排序
	while (gap > 1){
		gap = gap / 3 + 1;//控制最后一次进来gap为1进行直接插入排序
		for (int i = 0; i < size - gap; i++){
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0){
				if (tmp < arr[end]){
					arr[end + gap] = arr[end];
					end -= gap;
				}else{
					break;
				}
			}
			arr[end + gap] = tmp;
		}
	}
}
void SelectSort(int* arr, int size){//优化选择排序
//优化后一次遍历找到最大和最小值
	int begin = 0;
	int end = size - 1;
	while (begin < end){
		int mini = begin, maxi = begin;
		for (int i = begin + 1; i <= end; i++){//找到最大和最小值
			if (arr[i] < arr[mini]){
				mini = i;
			}
			if (arr[i] > arr[maxi]){
				maxi = i;
			}
		}
		swap(arr[mini], arr[begin]);
		//如果maxi = begin，上一步交换了begin和mini的值，会影响maxi指向的值
		if (maxi == begin){
			maxi = mini;
		}
		swap(arr[maxi], arr[end]);
		begin++;
		end--;
	}
}
void BubbleSort(int* const arr, const int len){
	for (int i = 1; i < len; i++){
		for (int j = 0; j < len - i; j++){
			if (arr[j] > arr[j + 1]){
				swap(arr[j], arr [j+1]);
			}
		}
	}
}
//快速排序优化方法：
//1.从数组的头中尾三个元素中选取中间值并与第一个元素替换作为key可以一定程度避免key值过大或过小问题
//2.在递归到一定程度数组长度较短时，可改用插入排序，数据量少时效率会更高
void QuickSort(int* const arr, const int begin, const int end){//hoare快速排序
	int left = begin;
	int right = end;
	int key_i = left;
	if (begin >= end)//递归结束条件
		return;
	while (left < right){
		//右边先走
		while (left < right&&arr[right] >= arr[key_i])//找比key_i 处小的值
			right--;
		while (left < right&&arr[left] <= arr[key_i])//找比key_i 处大的值
			left++;
		swap(arr[left], arr[right]);
	}
	swap(arr[key_i], arr[left]);
	QuickSort(arr, begin, left - 1);//递归
	QuickSort(arr, right + 1, end);
}
void QuickSort1(int* const arr, const int begin, const int end){//前后指针法
	int prev = begin;
	int cur = begin + 1;
	int key = begin;
	if (begin >= end)
		return;
	while (cur <= end){
		while (cur <= end && arr[cur] > arr[key])//cur去找小于key的值
			cur++;
		if (cur <= end){
			prev++;
			swap(arr[prev], arr[cur]);//将prev后一个值与cur处的值交换
			cur++;
		}
	}
	swap(arr[key], arr[prev]);
	for(int i=0;i<7;i++){
        cout<<arr[i]<<" ";
    }
	cout<<endl;
	QuickSort1(arr, begin, prev - 1);
	QuickSort1(arr, prev + 1, end);
}
//归并排序
void _MergeSort(int* const arr, const int begin, const int end, int* const arr_tmp){
	if (begin >= end)
		return;
    //首先先分解问题
	int mid = (begin + end) >> 1;
	_MergeSort(arr, begin, mid, arr_tmp);
	_MergeSort(arr, mid + 1, end, arr_tmp);
    //问题分解完后进行归并
	int head_left = begin;
	int head_right = mid + 1;
	int tmp_index = begin;
	while (head_left<=mid&& head_right<=end){
		if (arr[head_left] < arr[head_right]){//对左右两部分进行比较
			arr_tmp[tmp_index++] = arr[head_left++];
		}else{
			arr_tmp[tmp_index++] = arr[head_right++];
		}
	}
	//剩下的元素直接填充，因为有序
	while (head_left <= mid){
		arr_tmp[tmp_index++] = arr[head_left++];
	}
	while (head_right <= end){
		arr_tmp[tmp_index++] = arr[head_right++];
	}
	//建立时创建的数组的元素拷贝给原数组
	for (int i = begin; i <= end; i++){
		arr[i] = arr_tmp[i];
	}
}
void MergeSort(int* const arr, const int len)
{
	int *arr_tmp = (int*)malloc(sizeof(int)*len);
	_MergeSort(arr, 0, len - 1, arr_tmp);
	free(arr_tmp);
}
//计数排序
//只能是正整型
void CountSort(int* const arr, int length){
	assert(arr);
	//首先寻找最大值和最小值
    //确定新数组的大小
	int max=arr[0], min=arr[0];
	for (int i = 1; i < length; i++){
		if (max < arr[i]){
			max = arr[i];
		}
		if (min > arr[i]){
			min = arr[i];
		}
	}
	int range = max - min + 1;
	int* count = new int[sizeof(int)*range];
	memset(count, 0, sizeof(int)*range);//先初始化内存为零
	for (int i = 0; i < length; i++){//统计每个元素出现的次数
		count[arr[i]-min]++;
	}
	int j = 0;
	for (int i = 0; i < range; i++){//根据统计情况，重新覆盖原来数组
		while (count[i]--){
			arr[j++] = min + i;
		}
	}
	delete []count;
}
int main(){
    int a[]={4,3,2,1,5,7,6};
    //SelectSort(a,sizeof(a)/sizeof(int));
    //MergeSort(a,7);
	CountSort(a,7);
    for(int i=0;i<7;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}