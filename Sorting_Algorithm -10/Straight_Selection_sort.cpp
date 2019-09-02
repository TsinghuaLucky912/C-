#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

void Straight_Selection_sort1(vector<int>& src)
{
	int size = src.size();
	int count = 0;//���������Ĵ���
	for (int i = 0; i < size - 1; ++i)
	{
		int min = i;//Ĭ����Сֵ�±�		
		for (int j = i + 1; j < size ; ++j)
		{
			if (src[j] < src[min])
			{
				min = j;//��¼һ�� �µ���Сֵ�±�
			}
		}

		count++;
		std::swap(src[min], src[i]);

		cout << "��" << setw(2) << i + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
		
	}
	cout << "����������̹�������" << count << "�εĽ���" << endl;
}
void Straight_Selection_sort2(vector<int>& src)
{
	int size = src.size();
	int count = 0;//���������Ĵ���
	for (int i = 0; i < size - 1; ++i)
	{
		int min = i;//Ĭ����Сֵ�±�		
		for (int j = i + 1; j < size; ++j)
		{
			if (src[j] < src[min])
			{
				min = j;//��¼һ�� �µ���Сֵ�±�
			}
		}
		if (min != i)//���������Ԥ��
		{
			count++;
			std::swap(src[min], src[i]);
		}	
		cout << "��" << setw(2) << i + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}
	cout << "����������̹�������" << count << "�εĽ���" << endl;
}
int main()
{
	int Array[] = { 1,50,38,5,47,15,36,26,27,2,46,4,19,44,48 };
	vector<int>myvec(begin(Array), end(Array));

	Straight_Selection_sort1(myvec);
	cout << "������������ս����";
	for (int val : myvec)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "*******************************************" << endl;
	vector<int>myvec2(begin(Array), end(Array));
	Straight_Selection_sort2(myvec2);

	cout << "������������ս����";
	for (int val : myvec2)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	return 0;
}

