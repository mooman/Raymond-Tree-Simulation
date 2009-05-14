#ifndef EVENT_H_
#define EVENT_H_

class Request;

class Event {
    public:
        Event(string);
        Event(int, int, int, int, Request*);

        int get_time ();
        int get_site ();
        int get_from ();
        char get_action ();
        Request* request;

    private:
        int time;
        int site;
        int from;
        int action;

        void parse (string);
};

#endif /* EVENT_H_ */

