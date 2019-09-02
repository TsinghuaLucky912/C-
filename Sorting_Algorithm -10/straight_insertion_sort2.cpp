#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

void Straight_Insertion_Sort2(vector<int>& src)//ʹ�õ�����������ǰ��
{
	int size = src.size();
	int count = 0;//���������Ĵ���
	for (int i = 0; i < size - 1; ++i)
	{
		int j = i + 1;//ȡ���������еĵ�һ��Ԫ��
		int k = i;
		while (k >= 0 && src[j] < src[k])//���k�ıȽ� �����ǰ��
		{
			count++;
			swap(src[k], src[j]);
			k--;
			j--;
		}
		cout << "��" << setw(2) << i  + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}	
	cout << "����������̹�������" << count << "�εĽ���" << endl;
}


void Straight_Insertion_Sort1(vector<int>& src)//ʹ�õ���������ƣ�Ȼ�����
{
	int size = src.size();
	int count = 0;//�����ƶ��Ĵ���
	for (int i = 0; i < size - 1; ++i)
	{
		int j = i + 1;//ȡ���������еĵ�һ��Ԫ��
		int k = i;
		int tempval = src[j];
		while (k >= 0 && tempval < src[k])//���k�ıȽ� �����ǰ��
		{
			count++;
			src[j] = src[j - 1];
			k--;
			j--;
		}
		src[j] = tempval;//�������
		cout << "��" << setw(2) << i + 1 << "������󣬽��Ϊ��";
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

	Straight_Insertion_Sort1(myvec);
	cout << "������������ս����";
	for (int val : myvec)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	vector<int>myvec2(begin(Array), end(Array));
	Straight_Insertion_Sort2(myvec2);
	cout << "������������ս����";
	for (int val : myvec2)
	{
		cout << setw(2) << val << " ";
	}
	return 0;
}

