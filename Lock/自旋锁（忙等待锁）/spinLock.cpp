/*
 * 通过 testAndSet实现自旋锁，即忙等待锁
 *
 * 单核CPU不应该使用自旋锁，因为他会一直占有锁
 */

#include<iostream>
using namespace std;

int TestAndSet(int *old_ptr, int newdata){
    int old = *old_ptr;
    *old_ptr = newdata;
    return old;
}

typedef struct lock_t{
    int flag;
}lock_t;

void init(lock_t *lock){
    lock->flag = 0;
}

void lock(lock_t *lock){
    while(TestAndSet(&lock->flag, 1) == 1);

    ; // do something
}

void unlock(lock_t *lock){
    lock_t->flag = 0;
}