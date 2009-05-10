#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "site.h"
#include "simulator.h"

Messenger::Messenger (Simulator * s):
    wd_size(8)
{
    //hook in with the current simulator
    this->s = s;

    //weighted time delays, the index corresponds to the delay
    int wd[8] = {0, 300, 300, 200, 100, 50, 25, 25};
    weighted_delays = new int[8];
    for (int i = 0; i < wd_size; i++) {
        weighted_delays[i] = wd[i];
    }
}

void Messenger::send (int to, int from, int action) {
    if (to == from) {
        cout << "are you insane? you're sending a message to yourself. ignoring reuqest" << endl;
        return;
    }

    int time = s->get_current_time() + compute_delivery_delay();
    s->new_event(time, to, from, action);

    cout << "------ message is scheduled to deliver at time " << time << endl;
}

int Messenger::compute_delivery_delay () {
    int i, sum, r = rand() % 1000 + 1;
    for (i = sum = 0; i < wd_size; i++) {
        sum += weighted_delays[i];
        //does our random number fall within the distribution?
        if (r <= sum) return i;
    }

    //program should die if this happens
    exit(1);
}
