#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void Bubble_sort1(vector<int>& src)
{
	int size = src.size();
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (src[j] > src[j + 1])
			{
				int temp = src[j];
				src[j] = src[j + 1];
				src[j + 1] = temp;
			}
		}

		cout << "��" << setw(2) << i + 1 << "������󣬽��Ϊ��";
		for (int k=0;k<=size-1;++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}
}
void Bubble_sort2(vector<int>& src)
{
	int size = src.size();
	for (int i = 0; i < size - 1; ++i)
	{
		int flag = true;//ÿ��ѭ����ʼ Ĭ������ ����Ҫ����
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (src[j] > src[j + 1])
			{
				int temp = src[j];
				src[j] = src[j + 1];
				src[j + 1] = temp;
				flag = false;//��־Ϊ�� ����Ҫ����
			}
		}
		
		if (flag)
		{
			cout << "��Ȼ���� ����Ҫ��������" << endl;
			break;//
		}
		cout << "��" << setw(2) << i + 1 << "������󣬽��Ϊ��";
		for (int k = 0; k <= size - 1; ++k)
		{
			cout << setw(2) << src[k] << " ";
		}
		cout << endl;
	}
}
int main1()
{
	int Array[] = { 1,50,38,5,47,15,36,26,27,2,46,4,19,44,48 };
	vector<int>myvec(begin(Array), end(Array));

	Bubble_sort1(myvec);
	cout << "������������ս����";
	for (int val : myvec)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "*******************************************" << endl;
	vector<int>myvec2(begin(Array), end(Array));
	Bubble_sort2(myvec2);

	cout << "������������ս����";
	for (int val : myvec2)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	return 0;
}
