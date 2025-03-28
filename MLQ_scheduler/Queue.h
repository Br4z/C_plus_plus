#include <queue>

#include "scheduling_algorithm/SchedulingAlgorithm.h"
#include "MyProcess.h"

#ifndef QUEUE_H
#define QUEUE_H


class Queue {
	private:
		SchedulingAlgorithm* scheduling_algorithm;
		std::queue <Process*> processes;
	public:
		Queue();
		Queue(SchedulingAlgorithm* scheduling_algorithm);

		void add_process(Process* process);
		int run(int actual_time);

		std::string to_string() const;
};


#endif
