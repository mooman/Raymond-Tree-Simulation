#include "main.h"
#include "queue.h"
#include "event.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "site.h"
#include "simulator.h"

using namespace std;

int main (int argc, char ** argv) {
    string line;
    int nsites, max_time;

    //number of sites
    scanf("%d", &nsites);
    //max timeline
    scanf("%d", &max_time);

    Simulator * s = new Simulator(nsites, max_time);
    //the rest are events
    while (cin) {
        getline(cin, line);
        if (line.empty()) continue;

        //Event will parse the line
        s->new_event(line);
    }

//    s->start();
    return 0;
}
