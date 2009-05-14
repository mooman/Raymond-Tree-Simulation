#ifndef REQUEST_H_
#define REQUEST_H_

class Request
{
public:
	Request(int id);
	virtual ~Request();

	int num_messages;		// keep track of number of messages per request
	int site_id;
};

#endif /*REQUEST_H_*/
