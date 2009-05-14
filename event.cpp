#include "main.h"
#include "event.h"
#include "Request.h"

Event::Event(string line) {
    time, site, from, action, request = NULL;

    parse(line);
}

Event::Event(int t, int s, int f, int a, Request* r) {
    time = t;
    site = s;
    from = f;
    action = a;
    request = r;
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
