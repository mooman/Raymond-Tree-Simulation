#include "queue.h"

#define NULL 0x0

Queue::Queue() {
    head = NULL;
    tail = NULL;
}

void Queue::enqueue (void * obj) {
    if (head == NULL) {
        head = tail = new queue;
    } else {
        tail->next = new queue;
        tail = tail->next;
    }

    tail->obj = obj;
    tail->next = NULL;
}

void * Queue::dequeue () {
    void * ret = head->obj;
    head = head->next;
    return ret;
}
