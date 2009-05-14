#include "main.h"
#include "event.h"
#include "queue.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "site.h"
#include "simulator.h"
#include "Request.h"
#include "MessageTracker.h"

Site::Site(RaymondTree* tr, Simulator * s, Messenger * m) {
    this->tree_ptr = tr;
    this->m = m;
    this->s = s;

    request_q = new Queue();
    executing_cs = false;

    //stats init
    cs_requests = 0;
    //this will be just a cummative sum,
    //devide by requests to get average response time
    response_times = 0;
    times_request_cs = new Queue();
}

void Site::process_token_request (Event* e) {
    //do I have the token? am i using it?
    if (this->holder == this->site_id && !executing_cs) {
        //if i have the token, and im not using it,
        //it follows that the request queue must be empty
        //send the token or execute cs if it's me wanting
        if (e->get_from() == this->site_id) {
            //if the from request is from THIS site, then i want to execute
            execute_cs();
        } else {
            cout << "Site " << this->site_id << ": Queue empty, sending token to site " << e->get_from() << endl;
            if (e->request != NULL)
                e->request->num_messages++;
            m->send(e->get_from(), this->site_id, ACTION_TOKEN_GRANTED, e->request);
            //point my holder there
            this->holder = e->get_from();
        }

        return;
    } else {
        //any prior requests?
        if (request_q->empty()) {
            cout << "Site " << this->site_id << ": Don't have token. Queue empty, sending request to holder " << this->holder << endl;

            //if request queue is empty, it means i haven't sent a request yet
            //but i dont have token, so forward request
            if (e->request != NULL)
                e->request->num_messages++;
            m->send(this->holder, this->site_id, ACTION_TOKEN_REQUEST, e->request);
        } else {
            cout << "Site " << this->site_id << ": Already sent a token request, queue this one." << endl;
        }
    }

    request_q->enqueue(e);
}

void Site::process_token_received () {
    //request queue cant be empty, a token would not be granted
    //if there wasn't a request
    Event * e = (Event *) request_q->dequeue();
    cout << "Site " << this->site_id << ": Got token! Forwarding to site " << e->get_from() << endl;

    if (e->get_from() == this->site_id) {
        //hey! i requested it!
        cout << "##### That's me!" << endl;
        execute_cs();
    } else {
        m->send(e->get_from(), this->site_id, ACTION_TOKEN_GRANTED, e->request);
        if (!request_q->empty()) {
            cout << "++++++ Queue is not empty, sending also a request" << endl;
            m->send(e->get_from(), this->site_id, ACTION_TOKEN_REQUEST, e->request);
        }
    }

    //this could be THIS site, or the site it sent token to
    this->holder = e->get_from();

    s->holder_status();
}

void Site::execute_cs () {
    executing_cs = true;

    //execution time delay, schedule a release time with the simulator
    int time_delay = rand() % 10;
    s->new_event(s->get_current_time() + time_delay, this->site_id, this->site_id, ACTION_RELEASE_CS, NULL);

    cout << "Site " << this->site_id << " is executing CS. Will release in +" << time_delay << " unit time" << endl;
    s->mark_enter_cs();
}

void Site::release_cs () {
    executing_cs = false;

    if (!request_q->empty()) {
        Event * e = (Event *) request_q->dequeue();
        cout << "Site " << this->site_id << ": Released CS. Sending token to site " << e->get_from() << endl;

        if (e->get_from() == this->site_id) {
            //me again
            execute_cs();
        } else {
            m->send(e->get_from(), this->site_id, ACTION_TOKEN_GRANTED, NULL);
            if (!request_q->empty()) {
                cout << "++++++ Queue is not empty, sending also a request" << endl;
                m->send(e->get_from(), this->site_id, ACTION_TOKEN_REQUEST, e->request);
            }
        }

        this->holder = e->get_from();
    }

    //set simulator know we're done with CS, for stats
    s->mark_exit_cs();

    int *tr = (int *) times_request_cs->dequeue();
    time_finish_cs = s->get_current_time();
    response_times += time_finish_cs - *tr;
    delete(tr);
}

float Site::average_response_time () {
    if (cs_requests == 0) return 0;
    return ((float) response_times / cs_requests);
}

void Site::process_event (Event* e) {
    cout << "Site " << this->site_id << ": ";
    switch (e->get_action()) {
        case ACTION_TOKEN_REQUEST:
            if (e->get_from() == this->site_id) {
                cout << "Wants to enter CS" << endl;
                cs_requests++;
                int* tr = new int;
                *tr = s->get_current_time();
                times_request_cs->enqueue(tr);

                // see if this request was made before
                // if so, we don't want to create a new one
                Request* mRequest = MessageTracker::getInstance()->find(this->site_id);
                if (mRequest == NULL) {
                    mRequest = new Request(this->site_id);
                    MessageTracker::getInstance()->add(mRequest);
                    mRequest->num_messages++; // this step will always result in at least
                                              // one message being sent
                    e->request = mRequest;
                }

            } else {
                cout << "Received request for token from site " << e->get_from() << endl;
            }

            //figures out what to do with the request
            //default request of CS uses this case too.
            process_token_request(e);
            break;
        case ACTION_TOKEN_GRANTED:
            cout << "Token received from site " << e->get_from() << endl;
            process_token_received();
            break;
        case ACTION_RELEASE_CS:
            cout << "Finishes executing CS" << endl;
            release_cs();
            break;
        default:
            cout << "I dont know this action!" << endl;
            break;
    }
}
