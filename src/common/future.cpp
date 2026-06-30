#include "future.hpp"

JobQueue<futureJob> futureJobs;

void future_add(futureJobFunc callbackFunc, FutureData resultData) {
	futureJob newjob;

	newjob.callbackFunc = callbackFunc;
	newjob.resultData = resultData;

	futureJobs.push_back(newjob);
}

void do_future(void) {
	futureJobs.Run(
		[](futureJob& job) {
			job.callbackFunc(job.resultData);
		}
	);
}
