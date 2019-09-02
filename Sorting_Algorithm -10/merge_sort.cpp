#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <assert.h>
using namespace std;

//һֱ���µݹ� �������඼return��ʱ�򣬽��е��� ����֮�󷵻���һ�� ����
void Merge_sort_Recur(vector<int>& src, int low, int high)
{
	if (low == high)//�Ѽ���Ե������ڵݹ�ѭ�������
		return;
	int mid = (high - low) / 2 + low;

	Merge_sort_Recur(src, low, mid);
	Merge_sort_Recur(src, mid + 1, high);

	//���������ǽ��й鲢�ˣ��ݹ鿪ʼ�����ˣ�
	vector<int> tem_vec;//�������м���ɵ����ã������򲿷� ����
	tem_vec.resize(high - low + 1);

	int i = low, j = mid + 1, k = 0;//k����ʱ������±�
	while (i <= mid && j <= high)
	{
		if (src[i] > src[j])
		{
			tem_vec[k++] = src[j++];
		}
		else
		{
			tem_vec[k++] = src[i++];
		}
	}
	while (i <= mid)
	{
		tem_vec[k++] = src[i++];
	}
	while (j <= high)
	{
		tem_vec[k++] = src[j++];
	}

	//���ݴ������������
	//���������  �ð��������ݻ���src
	k = 0;
	for (int i = low; i <= high; ++i)
	{
		src[i] = tem_vec[k++];
	}
}

void merge_sort1(vector<int>& src)//�ݹ�汾
{
	int size = src.size();
	if (size <= 1)
		return;
	Merge_sort_Recur(src, 0, size - 1);
}


void MergeSortNonRecursion(vector<int>& src)
{
	int size = src.size();
	if (size <= 1)
		return;
	vector<int> tem_vec;//�������м���ɵ����ã������򲿷� ����
	tem_vec.resize(size);

	//����������һ�αȽ�2�����ڶ��αȽ�4���������αȽ�8��������
	for (int level = 1; level < size; level *= 2)
	{
		int left_min, left_max, right_min, right_max;
		//ÿ�ζ��Ǵ������ͷԪ�ؿ�ʼ  i=0
		for (left_min = 0; left_min < size - level; left_min = right_max)
		{
			right_min = left_max = left_min + level;
			right_max = left_max + level;

			//�ұߵ��±����ֵֻ��Ϊsize
			if (right_max > size)
			{
				right_max = size;
			}

			int k = 0;//k����ʱ������±�
			//�����ߵ����ݻ�û�ﵽ�ָ������ұߵ�����û����ָ��ߣ���ʼѭ��
			while (left_min < left_max && right_min < right_max)
			{
				if (src[left_min] < src[right_min])
				{
					tem_vec[k++] = src[left_min++];

				}
				else
				{
					tem_vec[k++] = src[right_min++];
				}
			}
			//����ѭ���������������������������ߵ��α���δ�����ô��Ҫ��
			//����ӻ�ȥ�����ܻ������ʣ�������ұߵ�û�����أ���ʵģ��һ�¾Ϳ���
			//֪��������ұ�û�����ô˵���ұߵ����ݱȽϴ���ʱҲ�Ͳ����ƶ�λ����

			while (left_min < left_max)
			{
				//���left_minС��left_max��˵��������ߵ����ݱȽϴ�
				//ֱ�Ӱ����ǽӵ������min֮ǰ����
				src[--right_min] = src[--left_max];
			}
			while (k > 0)
			{
				//���ź�����ǲ������鷵�ظ�k
				src[--right_min] = tem_vec[--k];
			}	
		}
	}
}

void merge_sort2(vector<int>& src)//�ǵݹ��ʵ��
{
	MergeSortNonRecursion(src);
}

int main()
{
	int Array[] = { 1,50,38,5,47,15,36,26,27,2,46,4,19,44,48 };

	int Array2[] = { 3,2,4,6,5 };
	vector<int>myvec(begin(Array), end(Array));
	merge_sort1(myvec);
	cout << "����shell_sort1���������ս����";
	for (int val : myvec)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	vector<int>myvec2(begin(Array), end(Array));
	merge_sort2(myvec2);
	cout << "����shell_sort2���������ս����";
	for (int val : myvec2)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;

	return 0;
}