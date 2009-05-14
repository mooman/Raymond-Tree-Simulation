#include "MessageTracker.h"
#include "Request.h"
#include <iostream>
#include <list>

using namespace std;

MessageTracker* MessageTracker::pInstance = 0;

MessageTracker::MessageTracker()
{
	// empty constructor
}

MessageTracker::~MessageTracker()
{
	// remove only existing instance of this object
	if (pInstance != 0)
		delete pInstance;
}

MessageTracker* MessageTracker::getInstance()
{
	// this method will create the only instance of
	// this class, once and only once, then return
	// it on request
	if (pInstance == 0) {
		pInstance = new MessageTracker();
	}
	return pInstance;
}

void MessageTracker::add(Request* r)
{
	// add the request to the request list
	list_req.push_back(r);
}

Request* MessageTracker::find(int id)
{
	list<Request*>::iterator iter;

	// search through the list to find the
	// request given by the input id
	for (iter = list_req.begin(); iter != list_req.end(); iter++)
	{
		if ((*iter)->site_id == id)
		{
			// found!
			return *iter;
		}
	}
	// if not found return null
	return NULL;
}

void MessageTracker::print_messages()
{
	list<Request*>::iterator iter;
	// just go through the list and print the messages
	for (iter = list_req.begin(); iter != list_req.end(); iter++)
	{
		cout << (*iter)->site_id << ": " << (*iter)->num_messages+1;
		cout << endl;
	}
}

