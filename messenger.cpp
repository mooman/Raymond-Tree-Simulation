#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"

Messenger::Messenger (int max_time):
    wd_size(8)
{
    timeline = new Queue[max_time];

    //weighted time delays, the index corresponds to the delay
    int wd[8] = {0, 300, 300, 200, 100, 50, 25, 25};
    for (int i = 0; i < wd_size; i++) {
        weighted_delays[i] = wd[i];
    }

    srand(time(NULL));
}

void Messenger::send (int site, int action) {
    int time = compute_delivery_time();

    Event * e = new Event(time, site, action);
    timeline[time].enqueue(e);
}

int Messenger::compute_delivery_time () {
    int i, sum, r = rand() % 1000 + 1;
    for (i = sum = 0; i < wd_size; i++) {
        sum += weighted_delays[i];
        //does our random number fall within the distribution?
        if (r <= sum) return i;
    }

    //program should die if this happens
    return -1;
}
