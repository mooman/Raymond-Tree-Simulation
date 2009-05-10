#include "main.h"
#include "queue.h"

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

bool Queue::empty () {
    return head == NULL;
}
