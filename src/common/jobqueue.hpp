#pragma once

#include <functional>
#include <mutex>
#include <vector>

template <typename JobType>
class JobQueue {
	std::vector<JobType> queue;
	std::mutex mt;

public:
	void Run(std::function<void(JobType&)> func) {
		std::unique_lock<std::mutex> lock(mt);

		if (!queue.size())
			return;

		std::vector<JobType> QueueForRunning(queue.size());
		QueueForRunning.assign(queue.begin(), queue.end());
		queue.clear();
		lock.unlock();

		for (auto& job : QueueForRunning)
			func(job);
	}

	void push_back(JobType v) {
		std::unique_lock<std::mutex> lock(mt);
		queue.push_back(v);
	}
};
