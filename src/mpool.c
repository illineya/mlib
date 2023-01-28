#include <mlib.h>

mpool_t *mpool_create(muint64_t size, int count) {
	mpool_t *p = (mpool_t *) calloc(1, sizeof(mpool_t));
	
	if(p) {
		p->pool = malloc(size * count);
		p->in = calloc(1, count);
		p->size = size;
		p->count = count;
		return p;
	}

	return NULL;
}

mpointer_t mpool_alloc(mpool_t *p) {
	mpointer_t d = NULL;

	for(int i=0; i<p->count; i++) {
		if(!p->in[i]) {
			p->in[i] = 1;
			d = &p->pool[p->size * i];
			break;
		}
	}

	return d;
}

void mpool_free(mpool_t *p, mconstpointer_t d) {
	unsigned int i = (d - p->pool) / p->size;
	if(i < p->count) {
		p->in[i] = 0;
	}
}

mpointer_t mpool_alloc_mt(mpool_t *p) {
	mpointer_t d = NULL;
	pthread_mutex_lock(&p->mutex);
	for(int i=0; i<p->count; i++) {
		if(!p->in[i]) {
			p->in[i] = 1;
			d = &p->pool[p->size * i];
			break;
		}
	}
	pthread_mutex_unlock(&p->mutex);

	return d;
}

void mpool_free_mt(mpool_t *p, mconstpointer_t d) {
	pthread_mutex_lock(&p->mutex);
	unsigned int i = (d - p->pool) / p->size;
	if(i < p->count) {
		p->in[i] = 0;
	}
	pthread_mutex_unlock(&p->mutex);
}

void mpool_destroy(mpool_t *p) {
	if(p) {
		free(p->pool);
		free(p);
	}
}