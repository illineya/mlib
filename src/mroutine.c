#include <mlib.h>

static void mroutine_func(mpointer_t udata) {
    MRoutineInfo_t *info = (MRoutineInfo_t *) udata;

    while(info->running) {
        pthread_mutex_lock(&info->routine->mutex);
        MRoutineData_t *data = (MRoutineData_t *) mqueue_pop(info->routine->queue);
        pthread_mutex_unlock(&info->routine->mutex);

        if(data) {
            data->func(data->data);
            if(data->destroy)
                data->destroy(data->data);
            free(data);
	        continue;
        }
        usleep(10);
    }
}

MRoutine_t *mroutine_init() {
    MRoutine_t *routine = calloc(1, sizeof(MRoutine_t));
    routine->cores = sysconf(_SC_NPROCESSORS_ONLN);
    routine->threads = calloc(routine->cores, sizeof(MRoutineInfo_t));
    routine->queue = mqueue_init();
    pthread_mutex_init(&routine->mutex, NULL);

    for(int i=0; i<routine->cores; i++) {
        MRoutineInfo_t *info = calloc(1, sizeof(MRoutineInfo_t));
        info->running = true;
        info->waiting = true;
        info->routine = routine;
        info->thread = mthread_create(mroutine_func, (mpointer_t) info);
        routine->threads[i] = info;

        char name[10];
        snprintf(name, 10, "mroutine%i", i);
        routine->sem = sem_open(name, 0);
    }

    return routine;
}

void mroutine_attach(MRoutine_t *routine, MThreadFunc func, mpointer_t udata, MThreadDestroyFunc destroy) {
    MRoutineData_t *data = malloc(sizeof(MRoutineData_t));
    data->func = func;
    data->destroy = destroy;
    data->data = udata;

    pthread_mutex_lock(&routine->mutex);
    mqueue_push(routine->queue, (mpointer_t) data);
    pthread_mutex_unlock(&routine->mutex);
}

void mroutine_deinit(MRoutine_t *routine) {
    if(routine) {
        while(true) {
            MRoutineData_t *data = (MRoutineData_t *) mqueue_pop(routine->queue);
            if(!data)
                break;
            if(data->destroy)
                data->destroy(data->data);
            free(data);
        }

        for(int i=0; i<routine->cores; i++) {
            routine->threads[i]->running = false;
            mthread_deinit(routine->threads[i]->thread);
            free(routine->threads[i]);
        }

        mqueue_deinit(routine->queue);
        free(routine);
    }
}
