#include "Nginx_memeory_pool.h"
#include <cstdio>

typedef struct Data stData;
struct Data//���� �����������ڴ�ŵĶ���  ��װ����Ҫ512�ֽ�
{
	char* ptr;//�ؼ���������ָ��������Դ����Ҳ���ǲ�һ����
	FILE* pfile;//ָ���ⲿ��Դ��ͬ ����رպ���Ҳ�Ͳ�ͬ
};
//���������� �û��Լ��ṩ���ⲿ��Դ������

void func1(void* p1)
{
	char* p = (char*)p1;
	printf("free ptr mem!\n");
	free(p);
}
void func2(void * pf1)
{
	FILE* pf = (FILE*)pf1;
	printf("close file!\n");
	fclose(pf);
}
int main()
{
	//memorypool.ngx_create_pool  ����ʵ���� Nginx_memory_pool�Ĺ��캯������
	Nginx_memory_pool memorypool;
	// 512 - sizeof(ngx_pool_t) - 4095   =>   ��Сֵ����max��
	ngx_pool_s* pool = (ngx_pool_s*)memorypool.ngx_create_pool(512);//����һ���ڴ��
	if (pool == nullptr)
	{
		printf("ngx_create_pool fail...");
		return -1;
	}

	void* p1 = memorypool.ngx_palloc(128); // ��С���ڴ�ط����
	if (p1 == nullptr)
	{
		printf("ngx_palloc 128 bytes fail...");
		return -2;
	}

	stData* p2 = (stData*)memorypool.ngx_palloc(512); // �Ӵ���ڴ�ط����
	if (p2 == nullptr)
	{
		printf("ngx_palloc 512 bytes fail...");
		return -3;
	}
	p2->ptr =(char *) malloc(12);//ָ����Ƕ��ϵ�һ����Դ
	strcpy(p2->ptr, "hello world");
	p2->pfile = fopen("data.txt", "w");//ָ�����һ���򿪵��ļ�


	//���ﻹ����ͨ�� �������Ѻ���ָ�뱣����������ʵ�� �����ص�
	//���ص����� ������Ӧ�Ĳ������ͷ��ڴ����ʼ��ַ
	ngx_pool_cleanup_s* c1 = memorypool.ngx_pool_cleanup_add(sizeof(char*));
	c1->handler = func1;//����ص�����
	c1->data = p2->ptr;

	ngx_pool_cleanup_s* c2 = memorypool.ngx_pool_cleanup_add(sizeof(FILE*));
	c2->handler = func2;
	c2->data = p2->pfile;//��Ϊ���� �����ص�����

	memorypool.ngx_destroy_pool();
	// 1.�������е�Ԥ�õ������� 2.�ͷŴ���ڴ� 3.�ͷ�С���ڴ�������ڴ�
	//memorypool.ngx_destroy_pool  ����ʵ���� Nginx_memory_pool�����캯������
	return 0;
}