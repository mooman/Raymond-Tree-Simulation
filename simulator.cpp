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
            switch (e->get_action()) {
                case ACTION_TOKEN_REQUEST:
                    m->send(e->get_site(), ACTION_TOKEN_REQUEST);
                    //ask the site what it wants to do with the event
                    break;
                case ACTION_TOKEN_GRANTED:
                    //ask the site what it wants to do with the event
                    break;
                case ACTION_REQ_DELIVERED:
                    break;
                case ACTION_TOK_DELIVERED:
                    break;
                default:
                    break;
            }
        }
    }
}
