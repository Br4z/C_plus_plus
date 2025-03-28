#include <vector>
#include <queue>

#include "MyProcess.h"
#include "Queue.h"

#ifndef MLQ_SCHEDULER_H
#define MLQ_SCHEDULER_H


class MLQScheduler {
	private:
		std::vector <Process> processes;
		std::vector <Queue> queues;
	public:
		MLQScheduler();

		std::vector <Process> get_processes();

		void add_process(Process process);
		void assign_processes();

		void run();

		std::string processes_to_string() const;
		std::string queues_to_string() const;
};


#endif
