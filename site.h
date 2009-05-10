#ifndef SITE_H_
#define SITE_H_
#include <queue>
#include "Request.h"
#include "RaymondTree.h"

class Site {
    public:
        //constructor
        Site(RaymondTree* tr);
        void request();
        void process_request(Request* r);
        void send_token();
        void receive_token();
        void execute_cs();
        void process_event (Event *);

        int id;
        Site* left;
        Site* right;
        bool token;

        // pointer to the parent site
        Site* holder;
        RaymondTree* tree_ptr;

    private:
        //queue<int> request_q;
        //int holder
};

#endif /*SITE_H_*/
