#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;


//�����ֱ�Ӳ�������
int Straight_Insertion_Sort1(vector<int>& src,int gap,int count)//ʹ�õ���������ƣ�Ȼ�����
{
	int size = src.size();
	for (int i = gap; i < size; ++i)
	{
		int j = i - gap;//ȡ���������еĵ�һ��Ԫ��
		int tempval = src[i];
		while (j >= 0 && tempval < src[j])//���k�ıȽ� �����ǰ��
		{
			count++;
			src[j + gap] = src[j];
			j -= gap;
		}
		src[j + gap] = tempval;
	}
	return count;
}
void shell_sort3(vector<int>& src)
{
	int size = src.size();
	int count = 0;
	int n = 0;
	for (int gap = size / 2; gap >= 1; gap /= 2)
	{
		count=Straight_Insertion_Sort1(src, gap, count);
		cout << "��" << setw(2) << n++ + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}
	cout << "����������̹�������" << count << "�ε��ƶ�" << endl;
}

//ʹ��  �򵥵���������gap = {n/2 ,n/4, n/8 .....1}
void shell_sort1(vector<int>& src)
{
	int size = src.size();
	int count = 0;//�����ƶ��Ĵ���

	int n = 0;
	for (int gap = size / 2; gap >= 1; gap /= 2)
	{
		int i = gap;
		for (; i < size; ++i)
		{
			int j = i - gap;
			int temp = src[i];
			while (j >= 0 && src[j] > temp)
			{
				count++;
				src[j + gap] = src[j];
				j -= gap;
			}
			src[j + gap] = temp;
		}
		
		cout << "��" << setw(2) << n++ + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}
	cout << "����������̹�������" << count << "�ε��ƶ�" << endl;
}
//ʹ�ø�����������gap={5,3,1}
void shell_sort2(vector<int>& src)
{
	int size = src.size();
	int count = 0;//�����ƶ��Ĵ���

	int n = 0, m = 0;
	int gapArr[] = { 5,3,1 };
	for (int gap = gapArr[m]; m<sizeof(gapArr)/sizeof(gapArr[0]);gap=gapArr[m])
	{
		m++;
		int i = gap;
		for (; i < size; ++i)
		{
			int j = i - gap;
			int temp = src[i];
			while (j >= 0 && src[j] > temp)
			{
				count++;
				src[j + gap] = src[j];
				j -= gap;
			}
			src[j + gap] = temp;
		}

		cout << "��" << setw(2) << n++ + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}
	cout << "����������̹�������" << count << "�ε��ƶ�" << endl;
}
int main()
{
	int Array[] = { 1,50,38,5,47,15,36,26,27,2,46,4,19,44,48 };

	vector<int>myvec(begin(Array), end(Array));
	shell_sort1(myvec);
	cout << "����shell_sort1���������ս����";
	for (int val : myvec)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	vector<int>myvec2(begin(Array), end(Array));
	shell_sort2(myvec2);
	cout << "����shell_sort2���������ս����";
	for (int val : myvec2)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	vector<int>myvec3(begin(Array), end(Array));
	shell_sort3(myvec3);
	cout << "����shell_sort3���������ս����";
	for (int val : myvec3)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	return 0;
}

