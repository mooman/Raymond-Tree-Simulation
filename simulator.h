#ifndef SIMULATORH
#define SIMULATORH

//forward declaration
class Messenger;

class Simulator {
    public:
        Simulator (int, int);

        void start ();
        void new_event (string);
        void new_event (int, int, int, int);
        int get_current_time ();
        void holder_status ();

    private:
        Queue * timeline;
        Messenger * m;
        Site ** s;
        RaymondTree * rt;

        int nsites;
        int max_time;
        int current_time;
};

#endif
