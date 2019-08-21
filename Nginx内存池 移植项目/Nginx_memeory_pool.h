#pragma once
/*
��Ŀ��ֲ1��Nginx�ڴ��Դ����ֲ������OOP˼���װʵ����Ŀ
*/
#include <cstdlib>
#include <string>
using u_char=unsigned char;      //�����ض���
using ngx_uint_t=unsigned int;
struct ngx_pool_s;               //����ǰ������һ�£�
/*
 * NGX_MAX_ALLOC_FROM_POOL should be (ngx_pagesize - 1), i.e. 4095 on x86.
 * On Windows NT it decreases a number of locked pages in a kernel.
 */
const int ngx_pagesize = 4096;//Ĭ��һ������ҳ��Ĵ�С 4K

//NginxС���ڴ�ؿ��Է�������ռ�
const int NGX_MAX_ALLOC_FROM_POOL = ngx_pagesize - 1;

const int NGX_DEFAULT_POOL_SIZE = 16 * 1024;//16K   Nginx�ڴ��Ĭ�Ͽ��ٴ�С

//�ڴ�ش�С����16�ֽڽ��ж���
const int NGX_POOL_ALIGNMENT = 16;

//������SGI STL�����ռ��������ڴ�ص� _S_round_up����
#define ngx_align(d, a)     (((d) + (a - 1)) & ~(a - 1))//�ϵ���������,������16�ֽڵı�����
//С���ڴ� ���俼���ֽڶ���ʱ�ĵ�λ��32λ4�ֽ�  64λ8�ֽ�
#define NGX_ALIGNMENT   sizeof(unsigned long)    /* platform word */

//��ָ��p ������a�ı���
#define ngx_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

//��buffer��������0
#define ngx_memzero(buf, n)       (void) memset(buf, 0, n)

//����ص�����������  ������һ������ָ��
typedef void (*ngx_pool_cleanup_pt)(void* data);

//�������ڴ�֮ǰ������ⲿ��Դ��  ����ص�����
struct ngx_pool_cleanup_s {
	ngx_pool_cleanup_pt   handler;//������һ�� ����ָ�룬������������Ļص�����
	void* data;                   //�����ص������Ĳ���
	ngx_pool_cleanup_s* next;     //��һ�� cleanup���������handler��
};


//����ڴ��ͷ����Ϣ
struct ngx_pool_large_s {
	ngx_pool_large_s* next;      //���еĴ���ڴ���䶼�Ǳ�����һ��������
	void* alloc;                 //��������ȥ�Ĵ���ڴ����ʼ��ַ
};


//����С���ڴ�� �ڴ��ͷ��������Ϣ
struct ngx_pool_data_t {         //  ����ͷ
	u_char* last;                //С���ڴ��  �ɷ���Ŀ����ڴ����ʼ��ַ
	u_char* end;                 //С���ڴ��  �ɷ���Ŀ����ڴ��ĩβ��ַ
	ngx_pool_s* next;            //�� ��ο��ٵ�С���ڴ�� �ڴ����������
	ngx_uint_t            failed;//ÿ��С���ڴ� �ڴ�ط���ʧ�ܣ���ʧ�ܴ���++
} ;

//Nginx�ڴ�� �ڴ�ͷ��Ϣ�͹�����Ϣ
struct ngx_pool_s {              
	ngx_pool_data_t       d;     //��ǰС���ڴ�ص�ʹ�����
	size_t                max;   //С���ڴ����ʹ���ڴ����ķֽ���
	ngx_pool_s* current;         //ָ���һ���ṩС���ڴ�����С���ڴ��
	ngx_pool_large_s* large;     //ָ�����ڴ������ ��ڵ�ַ
	ngx_pool_cleanup_s* cleanup; //ָ������Ԥ�õ�������� �ص�������������ڵ�ַ
};

//NginxС���ڴ����С��size���� ����ΪNGX_POOL_ALIGNMENT���ٽ�����
//����������ڴ�صð���� �ڴ�ͷ��2��ngx_pool_large_s�ڴ�ͷ
const int NGX_MIN_POOL_SIZE = ngx_align((sizeof(ngx_pool_s) +
	2 * sizeof(ngx_pool_large_s)), NGX_POOL_ALIGNMENT);
class Nginx_memory_pool          //Nginx�ڴ����
{
public:
	//�ڴ�ش������� size��С���ڴ�أ����ܳ���1��ҳ���С��
	void* ngx_create_pool(size_t size);

	//�����ڴ��ֽڶ��룬���ڴ������size�ֽ��ڴ�
	void* ngx_palloc(size_t size);
	//�������ڴ��ֽڶ��룬���ڴ������size�ֽ��ڴ�
	void* ngx_pnalloc(size_t size);
	//����ngx_palloc���������ڴ棬���ǻ��ʼ���ڴ�Ϊ 0
	void* ngx_pcalloc(size_t size);

	//�ͷŴ���ڴ�
	void  ngx_pfree(void* p);

	//�ڴ����ú���
	void ngx_reset_pool();

	//�ڴ�ص����ٺ���
	void ngx_destroy_pool();
	
	//����û��ṩ��  ����ص������ĺ���
	ngx_pool_cleanup_s* ngx_pool_cleanup_add(size_t size);
private:
	ngx_pool_s* pool_;          //ָ��Nginx�ڴ�ص����ָ��

	//С���ڴ����
	void* ngx_palloc_small(size_t size, ngx_uint_t align)
	{
		u_char* m;
		ngx_pool_s* p;

		p = pool_->current;

		do {
			m = p->d.last;

			if (align) {
				m = ngx_align_ptr(m, NGX_ALIGNMENT);
			}

			if ((size_t)(p->d.end - m) >= size) {
				p->d.last = m + size;

				return m;
			}

			p = p->d.next;

		} while (p);

		return ngx_palloc_block(size);
	}

	//�����µ��ڴ��
	void* ngx_palloc_block(size_t size)
	{
		u_char* m;
		size_t       psize;
		ngx_pool_s* p, * newpool;

		psize = (size_t)(pool_->d.end - (u_char*)pool_);

		m = (u_char*)malloc(psize);
		if (m == nullptr) {
			return nullptr;
		}

		newpool = (ngx_pool_s*)m;

		newpool->d.end = m + psize;
		newpool->d.next = nullptr;
		newpool->d.failed = 0;

		m += sizeof(ngx_pool_data_t);
		m = ngx_align_ptr(m, NGX_ALIGNMENT);
		newpool->d.last = m + size;

		for (p = pool_->current; p->d.next; p = p->d.next) {
			if (p->d.failed++ > 4) {
				pool_->current = p->d.next;
			}
		}

		p->d.next = newpool;

		return m;
	}

	//����ڴ����
	void* ngx_palloc_large(size_t size)
	{
		void* p;
		ngx_uint_t         n;
		ngx_pool_large_s* large;

		p = malloc(size);
		if (p == nullptr) {
			return nullptr;
		}

		n = 0;

		for (large = pool_->large; large; large = large->next) {
			if (large->alloc == nullptr) {
				large->alloc = p;
				return p;
			}

			if (n++ > 3) {
				break;
			}
		}

		large = (ngx_pool_large_s*)ngx_palloc_small(sizeof(ngx_pool_large_s), 1);
		if (large == nullptr) {
			free(p);
			return nullptr;
		}

		large->alloc = p;
		large->next = pool_->large;
		pool_->large = large;

		return p;
	}
};



















