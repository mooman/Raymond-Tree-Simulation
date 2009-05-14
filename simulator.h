#ifndef SIMULATORH
#define SIMULATORH

//forward declaration
class Messenger;
class Request;

class Simulator {
    public:
        Simulator (int, int);

        void start ();
        void new_event (string);
        void new_event (int, int, int, int, Request*);
        int get_current_time ();
        void holder_status ();
        void mark_enter_cs ();
        void mark_exit_cs ();

    private:
        Queue * timeline;
        Messenger * m;
        Site ** s;
        RaymondTree * rt;

        //stats var
        int cs_entries;
        int exit_cs_at;
        int sync_delays;


        int nsites;
        int max_time;
        int current_time;
};

#endif
