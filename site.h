#ifndef SITE_H_
#define SITE_H_

class Simulator;

class Site {
    public:
        //constructor
        Site(RaymondTree *, Simulator *, Messenger *);

        void process_event (Event *);
        void process_token_request (Event *);
        void process_token_received ();
        void execute_cs ();
        void release_cs ();
        float average_response_time ();

        //id for tree construction
        int id;
        //id based on user input
        int site_id;
        int holder;

        //stats variables
        int cs_requests;
        int response_times;
        Queue * times_request_cs;
        int time_finish_cs;

        // pointer to the parent site
        Site* parent;
        Site* left;
        Site* right;

        RaymondTree* tree_ptr;

    private:
        Queue * request_q;
        Messenger * m;
        Simulator * s;

        bool executing_cs;
};

#endif /*SITE_H_*/
