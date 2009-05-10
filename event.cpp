#include "main.h"
#include "event.h"

Event::Event(string line) {
    time, site, from, action = NULL;

    parse(line);
}

Event::Event(int t, int s, int f, int a) {
    time = t;
    site = s;
    from = f;
    action = a;
}

//accessors
int Event::get_time () {
    return time;
}

int Event::get_site () {
    return site;
}

int Event::get_from () {
    return from;
}

char Event::get_action () {
    return action;
}

void Event::parse (string line) {
    sscanf(line.c_str(), "%d %d %c", &time, &site, &action);
    from = site;
}
