#include "main.h"
#include "queue.h"
#include "event.h"
#include "simulator.h"

Simulator::Simulator (int ns, int mt) {
    nsites = ns;
    max_time = mt;

    timeline = new Queue[max_time];
}

void Simulator::new_event (string line) {
    Event * e = new Event(line);
    timeline[e->get_time()].enqueue(e);
}




void Simulator::start () {

}
