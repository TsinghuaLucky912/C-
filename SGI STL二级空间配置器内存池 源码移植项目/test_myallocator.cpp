#include "myallocator.h"
#include <vector>//�ռ������� �Ͼ��Ǹ�����ʹ�õ�

using namespace std;


int main()
{
	vector<int, myallocator<int>>myvec;

	//������ ���ǽ��в���ʹ����
	for (int i = 0; i < 10; ++i)
	{
		myvec.push_back(rand() % 100 + 1);
	}

	for (int val : myvec)
	{
		cout << val << endl;
	}
	return 0;
}



















