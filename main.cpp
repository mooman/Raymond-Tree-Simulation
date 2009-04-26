#include "main.h"
#include "queue.h"
//#include "simulator.h"
#include "event.h"

using namespace std;

int main (int argc, char ** argv) {
//    Simulator * s = new Simulator();
    Queue * timeline;
    Event * e;
    string line;
    int nsites, max_time;

    //number of sites
    cin >> line;
    //i dont know the best way to convert string to int in C++
    sscanf(line.c_str(), "%d", &nsites);

    //max timeline
    cin >> line;
    sscanf(line.c_str(), "%d", &max_time);

    timeline = new Queue[max_time];

    //the rest are events
    while (cin) {
        getline(cin, line);
        if (line.empty()) continue;

        e = new Event(line);
        timeline[e->get_time()].enqueue(e);
    }

//    s.start();
    return 0;
}
