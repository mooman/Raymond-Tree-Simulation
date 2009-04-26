#include <iostream>
#include "simulator.h"
#include "event.h"

using namespace std;

int main (int argc, char ** argv) {
    Simulator * s = new Simulator();
    Queue * timeline;
    Event * e;
    string line;
    int nsites, max_time;

    //number of sites
    cin >> line;
    //i dont know the best way to convert string to int in C++
    nsites = atoi(line.c_str());

    //max timeline
    cin >> line;
    max_time = atoi(line.c_str());

    timeline = new Queue[max_time];

    //the rest are events
    while (cin) {
        getline(cin, line);
        e = new Event(line);
        timeline[e->time()].enqueue(e);
    }

    s.start();
    return 0;
}
