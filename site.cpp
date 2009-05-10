#include "main.h"
#include "event.h"
#include "queue.h"
#include "messenger.h"
#include "RaymondTree.h"
#include "site.h"
#include "simulator.h"

Site::Site(RaymondTree* tr, Simulator * s, Messenger * m) {
	this->tree_ptr = tr;
    this->m = m;
    this->s = s;

    request_q = new Queue();

    executing_cs = false;
}

void Site::process_token_request (Event * e) {
    //do I have the token? am i using it?
    if (this->holder == this->site_id && !executing_cs) {
        //if i have the token, and im not using it,
        //it follows that the request queue must be empty
        //send the token or execute cs if it's me wanting

        if (!request_q->empty()) {
            cout << "AHHHH!! queue not empty!" << endl;
        }

        if (e->get_from() == this->site_id) {
            //if the from request is from THIS site, then i want to execute
            execute_cs();
        } else {
            cout << "Site " << this->site_id << ": Queue empty, sending token to site " << e->get_from() << endl;
            m->send(e->get_from(), this->site_id, ACTION_TOKEN_GRANTED);
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
            m->send(this->holder, this->site_id, ACTION_TOKEN_REQUEST);
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
        m->send(e->get_from(), this->site_id, ACTION_TOKEN_GRANTED);
        if (!request_q->empty()) {
            cout << "++++++ Queue is not empty, sending also a request" << endl;
            m->send(e->get_from(), this->site_id, ACTION_TOKEN_REQUEST);
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
    s->new_event(s->get_current_time() + time_delay, this->site_id, this->site_id, ACTION_RELEASE_CS);

    cout << "Site " << this->site_id << " is executing CS. Will release in +" << time_delay << " unit time" << endl;
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
            m->send(e->get_from(), this->site_id, ACTION_TOKEN_GRANTED);
            if (!request_q->empty()) {
                cout << "++++++ Queue is not empty, sending also a request" << endl;
                m->send(e->get_from(), this->site_id, ACTION_TOKEN_REQUEST);
            }
        }

        this->holder = e->get_from();
    }
}

/*
void Site::request() {
	// request for a critical section
	//if (request_q is empty && !token) {
		// send request message to parent
//		Request* m_request = new Request(this->id);
//		this->holder->process_request(m_request);

		// add request to own request_q
		// request_q.add(r);
	//}
}

void Site::process_request(Request* r) {
	// first check to see if I'm the root site
	if (this->token == true) {
		// I am!
		// send the token to the site that
		// requested it
		this->token = false;
		if (r->site_id == this->left->id) {
			// it came from the left side
			this->left->send_token();
		}
		else {
			// it must have come from the right
			this->right->send_token();
		}
	}
	else {
		// place the request in the request q
		// request_q.add(r);
		// send request to parent provided this
		// request is not already in queue
		//if (request_q.find(r) == 0) {
			this->holder->process_request(r);
		//}
	}
}

void Site::send_token() {
	this->token = true;
	this->receive_token();
}


void Site::receive_token() {
	// token received, delete top entry from request_q
	// and send token to the site in this entry
	 Request* r;// = request_q.top();
	 if (r->site_id == this->id) {
		 // set holder variable to point to self
		 this->holder = this;
		 // execute CS
		 execute_cs();
	 }
	 else if (r->site_id == this->left->id) {
		 this->holder = this->left;
		 this->left->send_token();
	 }
	 else {
		 this->holder = this->right;
		 this->right->send_token();
	 }
	 // in all cases, at this point we've released the token
	 this->token = false;
}

void Site::execute_cs() {
	// simulate enter CS
	// ...
	// simulate exit CS
	// 1. check request_q, if non empty delete top entry from it
	// send the token to that site and set holder variable to
	// point to that site
	//if (request_q.size() != 0) {
		// request_q.pop;
		//if (r->site_id == this->left->id) {
			this->holder = this->left;
			this->left->send_token();
		//}
		//else {
			this->holder = this->right;
			this->right->send_token();
		//}
	//}

	// 2. If the request_q is nonempty at this point, then the
	// site sends a REQUEST message to the site which is pointed
	// at by the holder variable.
	// if (request_q.size() != 0) {
		//this->holder->process_request(r);
	//}
	//else {
			tree_ptr->set_root(this);
	//}
	// exit(0); // we're done
}
*/

void Site::process_event (Event * e) {
    cout << "Site " << this->site_id << ": ";
    switch (e->get_action()) {
        case ACTION_TOKEN_REQUEST:
            if (e->get_from() == this->site_id) {
                cout << "Wants to enter CS" << endl;
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
            release_cs();
            break;
        default:
            cout << "I dont know this action!" << endl;
            break;
    }
}
