#pragma once

#include <functional>

#include "jobqueue.hpp"

typedef void* FutureData;
typedef std::function<void(FutureData)> futureJobFunc;

struct futureJob {
	futureJobFunc callbackFunc;
	FutureData resultData;
};

extern JobQueue<futureJob> futureJobs;

void future_add(futureJobFunc callbackFunc, FutureData resultData);
void do_future(void);
