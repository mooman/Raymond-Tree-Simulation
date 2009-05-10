#include "event.h"
#include "site.h"
#include "RaymondTree.h"

Site::Site(RaymondTree* tr) {
	tree_ptr = tr;
}

void Site::request() {
	// request for a critical section
	//if (request_q is empty && !token) {
		// send request message to parent
		Request* m_request = new Request(this->id);
		this->holder->process_request(m_request);

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

void Site::process_event (Event * e) {
    switch (e->get_action()) {
        case ACTION_TOKEN_REQUEST:
            m->send(e->get_site(), ACTION_TOKEN_REQUEST);
            //ask the site what it wants to do with the event
            break;
        case ACTION_TOKEN_GRANTED:
            //ask the site what it wants to do with the event
            break;
        case ACTION_REQ_DELIVERED:
            break;
        case ACTION_TOK_DELIVERED:
            break;
        default:
            break;
    }
}
