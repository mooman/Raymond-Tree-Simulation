#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "site.h"
#include "simulator.h"

Simulator::Simulator (int ns, int mt) {
    nsites = ns;
    max_time = mt;
    current_time = 0;

    timeline = new Queue[max_time];
    m = new Messenger(this);

    rt = new RaymondTree(this, m);
    //build a virtual tree construction
    rt->build_tree(nsites);
    rt->traverse(rt->get_root());

    s = new Site *[nsites];
    for (int i = 0; i < nsites; i++) {
        if (rt->postorder_q->empty()) {
            cout << "tree is empty prematurely" << endl;
        }
        s[i] = (Site *) rt->postorder_q->dequeue();

        //set Site properties based on the simulator
        s[i]->site_id = i;
    }

    if (!rt->postorder_q->empty()) {
        cout << "tree is not yet empty" << endl;
    }
}

int Simulator::get_current_time () {
    return current_time;
}

void Simulator::new_event (string line) {
    Event * e = new Event(line);
    timeline[e->get_time()].enqueue(e);
}

void Simulator::new_event (int time, int to, int from, int action) {
    Event * e = new Event(time, to, from, action);
    timeline[time].enqueue(e);
}

void Simulator::start () {
    int i;
    Event * e;

    for (i = current_time = 0; i < max_time; i++, current_time++) {
        while (!timeline[i].empty()) {
            e = (Event *) timeline[i].dequeue();
            s[e->get_site()]->process_event(e);
        }
    }
}
