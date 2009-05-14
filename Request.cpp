#include "Request.h"

Request::Request(int id)
{
	// this will help us keep track of
	// who sent this request
	site_id = id;
	num_messages = 0;
}

Request::~Request()
{
}
