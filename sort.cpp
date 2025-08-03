#include <iostream> 
#include <vector>
#include <stack>
#include <cstring>
using namespace std;

int n; 

//插入排序
void Insertsort(vector<int>& arr)
{
	for(int i = 0;i < n;i++)
	{
		int end = i;
		int tmp = arr[i+1];
		while(end >= 0)
		{
			if(arr[end] > tmp)
			{
				arr[end+1] = arr[end];
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end+1] = tmp;
	}
}

//希尔排序
void Shellsort1(vector<int>& arr)
{
	//1lu
	int gap = n;
	while(gap > 1)
	{
		gap/=2;
		for(int i = 0;i < gap;i++)
		{
			for(int j = i;j < n - gap;j+=gap)
			{
				int end = j;
				int tmp = arr[end + gap];
				while(end >=0)
				{
					if(arr[end]>tmp)
					{
						arr[end+gap] = arr[end];
						end-=gap;
					}
					else
					{
						break;
					}
				}
				arr[end+gap] = tmp;
			}
		}
	}
}
void Shellsort2(vector<int>& arr)
{
	//多路 
	int gap = n;
	while(gap > 1)
	{
		gap/=2;
		for(int i =0;i < n-gap;i++)
		{
			int end = i;
			int tmp = arr[i+gap];
			while(end >= 0)
			{
				if(arr[end]>tmp)
				{
					arr[end+gap] = arr[end];
					end-=gap;
				}
				else
				{
					break;
				}
			}
			arr[end+gap] = tmp;
		}
	}
}

//选择排序
void Selectsort(vector<int>& arr) 
{
	int left = 0,right = n-1;
	while(left < right)
	{
		int min = left;
		int max = left;
		for(int i = left +1;i <= right;i++)
		{
			if(arr[i] < arr[min])
			{
				min = i;
			}
			if(arr[i] > arr[max])
			{
				max = i;
			}		
		}
		swap(arr[left],arr[min]);
		if(max == left)
			max = min;
		swap(arr[right],arr[max]);
		left++;
		right--;
	}
}

//堆排序
void Adjustdown(vector<int>& arr,int parent,int m)
{
	int child = parent*2 + 1;
	while(child < m)
	{
		if(child + 1 < m && arr[child] < arr[child +1])
			child++;
		if(arr[child] > arr[parent]) 
		{
			swap(arr[child],arr[parent]);
			parent = child;
			child = parent*2 +1;
		}
		else
		{
			break;
		}
	}
}
void Heapsort(vector<int>& arr) 
{

	for(int i = (n - 1 - 1)/2;i >= 0;i--)
	{
		Adjustdown(arr,i,n);//建立大根堆 
	}
	int end = n - 1;
	while(end > 0)
	{
		swap(arr[0],arr[end]);
		Adjustdown(arr,0,end);//注意第三个参数 
		end --;
	}
}

//冒泡排序
void Bubblesort(vector<int>& arr)
{
	for(int i = 0;i < n-1;i++)
	{
		for(int j = 0;j < n - i -1;j++)
		{
			if(arr[j] > arr[j+1])
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}
}

//快速排序
void _Quicksort(vector<int>& arr,int begin,int end)
{
	if(begin >= end)
	{
		return;
	}
	int key = begin;
	int left = begin;
	int right = end - 1;
	while(left < right)
	{
		//右找小 
		while(left < right && arr[right] >= arr[key])
			right--;
		//左找大
		while(left < right && arr[left] <= arr[key]) 
			left++;
		swap(arr[left],arr[right]);
	}
	swap(arr[left],arr[key]);
	key = left;
	_Quicksort(arr,begin,key);
	_Quicksort(arr,key + 1,end);
}
void PartQuicksort(vector<int>& arr,int begin,int end)
{
	if(begin >= end)
		return;
	int left = begin;
	int right = end - 1;
	int key = arr[begin];
	int hole = begin;
	while(left < right)
	{
		while(left < right && arr[right] >= key)
			right--;
		arr[hole] = arr[right];
		hole = right;
		while(left < right && arr[left] <= key)
			left++;
		arr[hole] = arr[left];
		hole = left;
	}
	arr[hole] = key;
	PartQuicksort(arr,begin,hole);
	PartQuicksort(arr,hole+1,end);
}
void Part2Quicksort(vector<int>& arr,int begin,int end)
{
	if(begin >= end)
		return;
	int prev = begin;
	int cur = prev +1;
	int key = begin;
	while(cur <= end)
	{
		if(arr[cur] < arr[key] && ++prev != cur)
			swap(arr[prev],arr[cur]);
		cur++; 
	}
	swap(arr[prev],arr[key]);
	key = prev;
	Part2Quicksort(arr,begin,prev-1);
	Part2Quicksort(arr,prev+1,end);
}
void Quicksort(vector<int>& arr)
{
	//_Quicksort(arr,0,n);
	//PartQuicksort(arr,0,n);
	Part2Quicksort(arr,0,n-1);
}
//非递归快排
int Quicksort2(vector<int>& arr,int begin,int end)
{
	int hole = begin;
	int key = arr[begin];
	while(begin < end)
	{
		while(begin < end && arr[end] >= key)
			end--;
		arr[hole] = arr[end];
		hole = end;
		while(begin < end && arr[begin] <= key)
			begin++;
		arr[hole] = arr[begin];
		hole = begin;
	}
	arr[hole] = key;
	return hole;
}
void QuicksortNone(vector<int>& arr)
{
	stack<int> st;
	st.push(0);
	st.push(n-1);
	while(!st.empty())
	{
		int right = st.top();
		st.pop();
		int left = st.top();
		st.pop();
		int key = Quicksort2(arr,left,right);
		if(left < key - 1)
		{
			st.push(left);
			st.push(key - 1);
		}
		if(right > key + 1)
		{
			st.push(key + 1);
			st.push(right);
		}
	}
}

//归并排序
void _Mergesort(vector<int>& arr,int begin,int end,vector<int>& tmp)
{
	if(begin >= end)
		return;
	int mid = (begin+end)>>1;
	_Mergesort(arr,begin,mid,tmp);
	_Mergesort(arr,mid+1,end,tmp);
	int begin1 = begin;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = end;
	int i = begin;
	while(begin1 <= end1 && begin2 <= end2)
	{
		if(arr[begin1] < arr[begin2])
		{
			tmp[i++] = arr[begin1++];
		}
		else
		{
			tmp[i++] = arr[begin2++];
		}
	}
	while(begin1 <= end1)
	{
		tmp[i++] = arr[begin1++];
	}
	while(begin2 <= end2)
	{
		tmp[i++] = arr[begin2++];
	}
	for(int j = begin;j <= end;j++)
	{
		arr[j] = tmp[j];
	}
	//memcpy(arr + begin, tmp + begin, (end - begin + 1)*sizeof(int));
}
void Mergesort(vector<int>& arr) 
{
	vector<int> tmp(n,0);
	_Mergesort(arr,0,n-1,tmp);
}

//打印函数
void Print(vector<int>& arr)
{
	for(int i = 0;i < n;i++)
	{
		cout<<arr[i]<<" " ;
	}
	cout<<endl;
}

int main() 
{
//	cin>>n;
//	vector<int> arr(n);
	n = 7;
	vector<int> arr={3,6,4,1,7,0,5};
	//Insertsort(arr);
	//Shellsort(arr);
	//Selectsort(arr);
	//Heapsort(arr);
	//Bubblesort(arr);
	//Quicksort(arr);
	//QuicksortNone(arr);
	Mergesort(arr);
	Print(arr);
	return 0;
}
