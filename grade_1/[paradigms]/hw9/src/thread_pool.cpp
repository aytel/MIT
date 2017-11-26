#include "thread_pool.h"
#include <unistd.h>
#include <iostream>

void *consumer(void *data) {
    ThreadPool *pool = (ThreadPool *)data;
    while (1) {
        pthread_mutex_lock(&pool->m);
        while (pool->tasks.empty() && !pool->to_ret) {
            pthread_cond_wait(&pool->cond, &pool->m);
        }
        if (pool->to_ret) {
            pool->closed++;
            pthread_mutex_unlock(&pool->m);
            break;
        }
        Task *cur = pool->tasks.front();
        pool->tasks.pop();
        pthread_mutex_unlock(&pool->m);

        cur->eval();
        delete cur;

        pthread_mutex_lock(&pool->m);
        pool->started--;
        if (pool->in_destr && !pool->started) {
            pthread_cond_signal(&pool->ret);
        }
        pthread_mutex_unlock(&pool->m);
    }
    return NULL;
}

Task::Task(void (*f)(void *), void *arg): f(f), arg(arg) {
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&m, NULL);
};

Task::~Task() {
    pthread_cond_destroy(&cond);
}

void Task::eval() {
    pthread_mutex_lock(&m);
    f(arg);
    pthread_mutex_unlock(&m);
}

void Task::wait() {
    pthread_mutex_lock(&m);
    pthread_mutex_unlock(&m);
}

ThreadPool::ThreadPool(unsigned threads_nm): to_ret(0), in_destr(0), started(0), closed(0) {
    threads.resize(threads_nm);
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&ret, NULL);
    for (unsigned i = 0; i < threads_nm; i++) {
        pthread_create(&threads[i], NULL, consumer, (void *)this);
    }
}

ThreadPool::~ThreadPool() {
    pthread_mutex_lock(&m);
    in_destr = 1;
    while (started) {
        pthread_cond_wait(&ret, &m);
    }
    to_ret = 1;
    pthread_mutex_unlock(&m);
    while (closed != threads.size()) {
        pthread_cond_signal(&cond);
    }
    for (unsigned i = 0; i < threads.size(); i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&ret);
    pthread_mutex_destroy(&m);
}

void ThreadPool::submit(Task *task) {
    pthread_mutex_lock(&m);
    tasks.push(task);
    started++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&m);
}