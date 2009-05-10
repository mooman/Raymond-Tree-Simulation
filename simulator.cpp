#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"
#include "simulator.h"

Simulator::Simulator (int ns, int mt) {
    nsites = ns;
    max_time = mt;
    current_time = 0;

    timeline = new Queue[max_time];
    m = new Messenger(this);
//    s = new Site(m);
}

int Simulator::get_current_time () {
    return current_time;
}

void Simulator::new_event (string line) {
    Event * e = new Event(line);
    timeline[e->get_time()].enqueue(e);
}

void Simulator::new_event (int time, int site, int action) {
    Event * e = new Event(time, site, action);
    timeline[time].enqueue(e);
}

void Simulator::start () {
    int i;
    Event * e;

    for (i = 0; i < max_time; i++) {
        while (!timeline[i].empty()) {
            e = (Event *) timeline[i].dequeue();
            site[e->get_site()].process_event(e);
        }
    }
}
