#include "thread_pool.h"
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <time.h>

struct args;

std::vector<args*> to_del;
pthread_mutex_t m;

struct args {
    std::vector<int>::iterator bg, en;
    ThreadPool *pool;
    int depth;
    args(std::vector<int>::iterator bg, std::vector<int>::iterator en, ThreadPool *pool, int depth):
    bg(bg), en(en), pool(pool), depth(depth) {
        pthread_mutex_lock(&pool->m);
        to_del.push_back(this);
        pthread_mutex_unlock(&pool->m);
    }
};

void pqsort(void *_arg) {
    args *arg = (args *)_arg;
    auto bg = arg->bg, en = arg->en;
    auto pool = arg->pool;
    auto depth = arg->depth;
    int len = en - bg;
    if (len < 2) {
        return;
    }
    if (depth < 0) {
        std::sort(bg, en);
        return;
    }
    int pivot = *(bg + rand() % len);
    auto left_bound = std::partition(bg, en, [&](int cur){
        return cur < pivot;
    });
    auto right_bound = std::partition(left_bound, en, [&](int cur){
        return cur <= pivot;
    });
    auto left_task = new args(bg, left_bound, pool, depth - 1);
    auto right_task = new args(right_bound, en, pool, depth - 1);
    pool->submit(new Task(pqsort, (void *)left_task));
    pool->submit(new Task(pqsort, (void *)right_task));
}

int main(int, char **argv) {
    srand(42);

    int threads_nm = atoi(argv[1]), size = atoi(argv[2]), depth = atoi(argv[3]);

    pthread_mutex_init(&m, NULL);
    std::vector < int > to_sort(size);
    for (int i = 0; i < size; i++) {
        to_sort[i] = rand();
    }

    ThreadPool *pool = new ThreadPool(threads_nm);
    pool->submit(new Task(pqsort, new args(to_sort.begin(), to_sort.end(), pool, depth)));
    delete pool;

    for (auto i : to_del) {
        delete i;
    }

    for (int i = 1; i < size; i++) {
        if (to_sort[i] < to_sort[i - 1]) {
            std::cout << "Failed\n";
            return 0;
        }
    }

    std::cout << "OK\n";

    pthread_mutex_destroy(&m);

    return 0;
}