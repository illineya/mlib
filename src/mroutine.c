#include <mlib.h>

void mroutine_func(mpointer_t udata) {
    MRoutineInfo_t *info = (MRoutineInfo_t *) udata;

    while(info->running) {
        pthread_mutex_lock(&info->routine->mutex);

        MRoutineData_t *data = (MRoutineData_t *) mqueue_pop(info->routine->queue);
        if(data)
            data->func(data->data);
    }
}

MRoutine_t *mroutine_init() {
    MRoutine_t *routine = calloc(1, sizeof(MRoutine_t));
    routine->cores = 2;
    routine->queue = mqueue_init();
    pthread_mutex_init(&routine->mutex, NULL);
    pthread_mutex_lock(&routine->mutex);

    for(int i=0; i<routine->cores; i++) {
        MRoutineInfo_t *info = malloc(sizeof(MRoutineInfo_t));
        info->running = TRUE;
        info->routine = routine;
        info->thread = mthread_create(mroutine_func, (mpointer_t) info);
        routine->threads[i] = info;
    }

    return routine;
}

void mroutine_attach(MRoutine_t *routine, MThreadFunc func, mpointer_t udata, MThreadDestroyFunc destroy) {
    MRoutineData_t *data = malloc(sizeof(MRoutineData_t));
    data->func = func;
    data->destroy = destroy;
    data->data = udata;

    mqueue_push(routine->queue, (mpointer_t) data);
    pthread_mutex_unlock(&routine->mutex);
}

void mroutine_deinit(MRoutine_t *routine) {
    if(routine) {
        while(TRUE) {
            MRoutineData_t *data = (MRoutineData_t *) mqueue_pop(routine->queue);
            if(!data)
                break;
            if(data->destroy)
                data->destroy(data->data);
            free(data);
        }

        for(int i=0; i<routine->cores; i++)
            routine->threads[i]->running = FALSE;

        mqueue_deinit(routine->queue);
        pthread_mutex_destroy(&routine->mutex);
    }
}