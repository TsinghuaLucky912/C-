
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

int one_Partition(vector<int>& src, int low, int high)
{
	static int n = 1;//��¼������
	int l = low, h = high;
	int pivotkey = src[l];//��������ݵĵ�һ������ ��Ϊ��׼ֵ

	while (l < h)
	{
		while (l < h  && src[h]>= pivotkey)
		{
			h--;
		}
		swap(src[l], src[h]);//��pivotkey�src��h�����棬��src��l��������ں���

		while (l < h && src[l] <= pivotkey)
		{
			l++;
		}
		swap(src[l], src[h]);//��pivotkey�src��l�����棬��src��h��������ں���
	}
	//src[l] = pivotkey;//����ǰ�pivotkey �ŵ����һ��λ��
	//�����Ҹо������������ Ҳ���Բ���д����Ϊ�������� �������ݣ���������������

	cout << "��" << n++ << "�ε��������󣬽����";
	for (int val : src)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	return l;//������±� ���أ���Ϊ��һ�εݹ��base�м���
}

void Quick_sort(vector<int>& src,int low,int high)
{
	int base = one_Partition(src, low, high);

	if (low + 1 < base)
		Quick_sort(src, low, base - 1);//�ݹ����

	if (base + 1 < high)
		Quick_sort(src, base + 1, high);//�ݹ��ұ�
}

int main()
{
	int Array[] = { 1,50,38,5,47,15,36,26,27,2,46,4,19,44,48 };
	int Array2[] = { 49,38,65,97,76,13,27,49 };
#if 0
	vector<int>myvec(begin(Array), end(Array));
	Quick_sort(myvec, 0, myvec.size() - 1);
	cout << "����Quick_sort���������ս����";
	for (int val : myvec)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
#endif
	vector<int>myvec2(begin(Array2), end(Array2));
	Quick_sort(myvec2, 0, myvec2.size() - 1);
	cout << "����Quick_sort���������ս����";
	for (int val : myvec2)
	{
		cout << setw(2) << val << " ";
	}
	cout << endl;
	return 0;
}
