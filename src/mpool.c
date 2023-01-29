#include <mlib.h>

MPool_t *mpool_create(muint64_t size, int count) {
    MPool_t *p = (MPool_t *) malloc(sizeof(MPool_t));
	
	if(p) {
		p->pool = malloc(size * count);
		p->in = calloc(1, count);
		p->size = size;
		p->count = count;
        pthread_mutex_init(&p->mutex, NULL);
		return p;
	}

	return NULL;
}

mpointer_t mpool_alloc(MPool_t *p) {
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

void mpool_free(MPool_t *p, mconstpointer_t d) {
	unsigned int i = (d - p->pool) / p->size;
	if(i < p->count) {
		p->in[i] = 0;
	}
}

mpointer_t mpool_alloc_mt(MPool_t *p) {
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

void mpool_free_mt(MPool_t *p, mconstpointer_t d) {
	pthread_mutex_lock(&p->mutex);
	unsigned int i = (d - p->pool) / p->size;
	if(i < p->count) {
		p->in[i] = 0;
	}
	pthread_mutex_unlock(&p->mutex);
}

void mpool_destroy(MPool_t *p) {
	if(p) {
		free(p->pool);
        pthread_mutex_destroy(&p->mutex);
		free(p);
	}
}