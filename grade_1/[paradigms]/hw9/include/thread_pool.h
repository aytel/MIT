#include <pthread.h>
#include <queue>

struct Task {
    void (*f)(void *);
    void *arg;
    pthread_cond_t cond;
    pthread_mutex_t m;

    Task(void (*f)(void *), void *arg);
    ~Task();

    void wait();
    void eval();
};

struct ThreadPool {
    std::vector < pthread_t > threads;
    std::queue < Task * > tasks;
    pthread_mutex_t m;
    pthread_cond_t cond, ret;
    bool to_ret, in_destr;
    unsigned started, closed;

    ThreadPool(unsigned threads_nm);
    ~ThreadPool();

    void submit(Task *task);
};