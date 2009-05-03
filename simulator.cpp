#include "main.h"
#include "queue.h"
#include "event.h"
#include "simulator.h"

Simulator::Simulator (int ns, int mt) {
    nsites = ns;
    max_time = mt;
    current_time = 0;

    timeline = new Queue[max_time];
    m = new Messenger(this);
}

void Simulator::get_current_time () {
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

}
