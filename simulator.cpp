#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "site.h"
#include "simulator.h"

Simulator::Simulator (int ns, int mt) {
    nsites = ns;
    max_time = mt * 100;
    current_time = 0;
    cs_entries = 0;
    exit_cs_at = 0;
    sync_delays = 0;

    timeline = new Queue[max_time];
    m = new Messenger(this);

    rt = new RaymondTree(this, m);
    //build a virtual tree construction
    rt->build_tree(nsites);
    rt->traverse(rt->get_root());

    int i;
    s = new Site *[nsites];
    for (i = 0; i < nsites; i++) {
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


    for (i = 0; i < nsites; i++) {
        if (s[i]->parent == NULL) {
            s[i]->holder = s[i]->site_id;
        } else {
            s[i]->holder = s[i]->parent->site_id;
        }
    }

    holder_status();
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

//print out current "tree"
void Simulator::holder_status () {
    cout << endl << "****** Holder Status ********" << endl;
    for (int i = 0; i < nsites; i++) {
        cout << "Site " << i << ": " << s[i]->holder << endl;
    }
    cout << "***********************" << endl;
}

void Simulator::mark_exit_cs () {
    exit_cs_at = current_time;
}

void Simulator::mark_enter_cs () {
    cs_entries++;
    sync_delays += current_time - exit_cs_at;
}

void Simulator::start () {
    int i, trt, rt = 0;
    Event * e;

    for (i = current_time = 0; i < max_time; i++, current_time++) {
        if (timeline[i].empty()) continue;

        cout << "\n\n----------- Time " << current_time << " ----------" << endl;
        while (!timeline[i].empty()) {
            e = (Event *) timeline[i].dequeue();
            s[e->get_site()]->process_event(e);
        }
    }

    cout << "\n\nFinished simulation...... here are some stats:\n" << endl;
    cout << "Average Response Times: " << endl;
    for (i = 0; i < nsites; i++) {
        trt = s[i]->average_response_time();
        rt += trt;
        cout << "Site " << i << ": " << trt << endl;
    }
    cout << "Overall Average: " << ((float) rt / nsites) << endl;

    cout << "\nAverage Sync Delay: " << ((float) sync_delays / cs_entries) << endl;
}
