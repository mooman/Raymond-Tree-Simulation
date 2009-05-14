#ifndef MESSAGETRACKER_H_
#define MESSAGETRACKER_H_

#include <iostream>
#include <list>

// forward declarations
class Request;

class MessageTracker
{
public:
	MessageTracker();				// constructor
	static MessageTracker* getInstance();
	void add(Request* r);			// add a request to list of requests
	Request* find(int id);			// find a particular request in the list
	void print_messages();			// print the number of messages per CS request
	virtual ~MessageTracker();		// destroy the object

private:
	static MessageTracker* pInstance;
	std::list<Request*> list_req;
};

#endif /*MESSAGETRACKER_H_*/
