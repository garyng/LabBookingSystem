#pragma once
#include <string>
#include <enum.h>

BETTER_ENUM(RequestStatus, int, Pending, Accepted, Rejected);

class Request
{
public:
	int RequestId;
	RequestStatus Status;

	Request(int requestId, const RequestStatus& status)
		: RequestId(requestId),
		  Status(status)
	{
	}
};
