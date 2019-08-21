#include "Nginx_memeory_pool.h"


//��Ҫ�� ��ʼ�����ڴ���� �����йصĹ�����Ϣ
//�ڴ�ش������� size��С���ڴ�أ����ܳ���1��ҳ���С��
void * Nginx_memory_pool::ngx_create_pool(size_t size)
{
	ngx_pool_s* p;

	p = (ngx_pool_s*)malloc(size);
	if (p == nullptr) {
		return nullptr;
	}

	p->d.last = (u_char*)p + sizeof(ngx_pool_s);
	p->d.end = (u_char*)p + size;
	p->d.next = nullptr;
	p->d.failed = 0;

	size = size - sizeof(ngx_pool_s);//��ȥ�ڴ�ͷ����
	p->max = (size < NGX_MAX_ALLOC_FROM_POOL) ? size : NGX_MAX_ALLOC_FROM_POOL;

	p->current = p;
	p->large = nullptr;
	p->cleanup = nullptr;

	pool_ = p;//����ط� p��һ���ֲ�����
	return p;
}
/*
size = size - sizeof(ngx_pool_s);//��ȥ�ڴ�ͷ����
����֮��sizeҪ��NGX_MAX_ALLOC_FROM_POOL�Ƚϡ�
max��ֵ��С��size���������NGX_MAX_ALLOC_FROM_POOL ���ܳ���һ��ҳ��
��Ϊ�ڴ������ͨ��lastָ��ƫ����ɵģ�����һ������ҳ���ϣ��ڴ治һ��������
�����Ļ�����ͨ��ָ��ƫ�ƣ�Ч�ʻ�ܵ͵ġ�

*/
//�����ڴ��ֽڶ��룬���ڴ������size�ֽ��ڴ�
void* Nginx_memory_pool::ngx_palloc(size_t size)
{
	if (size <= pool_->max) {
		return ngx_palloc_small(size, 1);
	}
	return ngx_palloc_large(size);
}

//�������ڴ��ֽڶ��룬���ڴ������size�ֽ��ڴ�
void* Nginx_memory_pool::ngx_pnalloc(size_t size)
{
	if (size <= pool_->max) {
		return ngx_palloc_small(size, 0);
	}
	return ngx_palloc_large(size);
}

//����ngx_palloc���������ڴ棬���ǻ��ʼ���ڴ�Ϊ 0
void* Nginx_memory_pool::ngx_pcalloc(size_t size)
{
	void* p;

	p = ngx_palloc(size);
	if (p) {
		ngx_memzero(p, size);//��0
	}

	return p;
}

//�ͷŴ���ڴ�
void Nginx_memory_pool::ngx_pfree(void* p)
{
	ngx_pool_large_s* l;

	for (l = pool_->large; l; l = l->next) {
		if (p == l->alloc) {
			free(l->alloc);
			l->alloc = nullptr;

			return;
		}
	}
}

//�ڴ����ú���
void Nginx_memory_pool::ngx_reset_pool()
{
	ngx_pool_s* p;
	ngx_pool_large_s* l;

	for (l = pool_->large; l; l = l->next) {
		if (l->alloc) {
			free(l->alloc);
		}
	}
	/*
	for (p = pool_; p; p = p->d.next) {
		p->d.last = (u_char*)p + sizeof(ngx_pool_s);
		p->d.failed = 0;
	}
	*/
	//�����һ���ڴ�� �ڴ��
	p = pool_;
	p->d.last = (u_char*)p + sizeof(ngx_pool_s);
	p->d.failed = 0;
	//���������ڴ�� �ڴ��
	for (p = p->d.next; p; p = p->d.next) {
		p->d.last = (u_char*)p + sizeof(ngx_pool_s);
		p->d.failed = 0;
	}
	pool_->current = pool_;
	pool_->large = nullptr;
}

//�ڴ�ص����ٺ���
void Nginx_memory_pool::ngx_destroy_pool()
{
	ngx_pool_s* p, * n;
	ngx_pool_large_s* l;
	ngx_pool_cleanup_s* c;

	for (c = pool_->cleanup; c; c = c->next) {
		if (c->handler) {
			c->handler(c->data);
		}
	}

	for (l = pool_->large; l; l = l->next) {
		if (l->alloc) {
			free(l->alloc);
		}
	}

	for (p = pool_, n = pool_->d.next; /* void */; p = n, n = n->d.next) {
		free(p);

		if (n == nullptr) {
			break;
		}
	}
}

//����û��ṩ��  ����ص������ĺ���
ngx_pool_cleanup_s* Nginx_memory_pool::ngx_pool_cleanup_add(size_t size)
{
	ngx_pool_cleanup_s* c;

	c = (ngx_pool_cleanup_s*)ngx_palloc(sizeof(ngx_pool_cleanup_s));
	if (c == nullptr) {
		return nullptr;
		}

	if (size) {
		c->data = ngx_palloc(size);
		if (c->data == nullptr) {
			return nullptr;
		}

	}
	else {
		c->data = nullptr;
	}

	c->handler = nullptr;
	c->next = pool_->cleanup;

	pool_->cleanup = c;

	
	return c;
}
