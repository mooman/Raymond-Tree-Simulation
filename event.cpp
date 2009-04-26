#include "main.h"
#include "event.h"

Event::Event(string line) {
    time, site, compute_duration, action = NULL;

    parse(line);
}

//accessors
int Event::get_time () {
    return time;
}

int Event::get_site () {
    return site;
}

char Event::get_action () {
    return action;
}

void Event::parse (string line) {
    sscanf(line.c_str(), "%d %d %c %d", &time, &site, &action, &compute_duration);
}

void Event::execute () {
}
